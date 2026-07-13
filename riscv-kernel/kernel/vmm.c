#include "vmm.h"
#include "pmm.h"
#include "uart.h"

// puntero a la tabla de paginas raiz
static uint64_t *root_page_table = NULL;

// get la direccion fisica de una tabla desde un puntero virtual
static inline uintptr_t get_physical_addr(void *ptr)
{
    // en mapeo, virt = fisica
    return (uintptr_t)ptr;
}

// crear tabla de paginsa de un nivel
static uint64_t *create_page_table(void)
{
    // asignar una pagina fisica para la tabla
    void *table = pmm_alloc_page();
    if (!table)
    {
        uart_puts("Error: no se pudo asignar pagina para la tabla de paginas\n");
        return NULL;
    }

    // poner toda la tabla a 0;
    for (int i = 0; i < PT_ENTRIES; i++)
    {
        ((uint64_t *)table)[i] = 0;
    }
    return (uint64_t *)table;
}

// mapear pagina virtual a fisica
static void map_page(uint64_t *root, uintptr_t virt, uintptr_t phys, uint64_t flags)
{
    uint64_t l2_index = (virt >> 30) & 0x1FF; // bits 38-30
    uint64_t l1_index = (virt >> 21) & 0x1FF; // bits 29-21
    uint64_t l0_index = (virt >> 12) & 0x1FF; // bits 20-12

    // directorio de paginas
    uint64_t *l2_table = root;
    uint64_t l2_entry = l2_table[l2_index];

    // si la entrada l2 no es valida, crear una tabla l1
    if (!(l2_entry & PTE_VALID))
    {
        uint64_t *l1_table = create_page_table();
        if (!l1_table)
        {
            uart_puts("Error: No se pudo crear tabla L1\n");
            return;
        }
        l2_table[l2_index] = get_physical_addr(l1_table) | PTE_VALID;
    }

    // obtener la direccion fisica de la tabla l1 desde la entrada l2
    uint64_t *l1_table = (uint64_t *)(l2_table[l2_index] & PTE_ADDR_MASK);

    // nviel 1: directorio de paginas superior
    uint64_t l1_entry = l1_table[l1_index];

    // si la entrada l1 no es valida, crear una tabla l0
    if (!(l1_entry & PTE_VALID))
    {
        uint64_t *l0_table = create_page_table();
        if (!l0_table)
        {
            uart_puts("Error: no se pudo crear tabla l0\n");
            return;
        }
        // configurar la entrada l1 para que apunte a la tabla l0
        l1_table[l1_index] = get_physical_addr(l0_table) | PTE_VALID;
    }
    uint64_t *l0_table = (uint64_t *)(l1_table[l1_index] & PTE_ADDR_MASK);

    // nivel 0: tabla de paginas
    // configurar la entrada l0 con la direccion fisica y los flags
    l0_table[l0_index] = (phys & PTE_ADDR_MASK) | flags;
}

void vmm_init(void)
{
    uart_puts("Inicializando VMM (Sv39)...\n");

    root_page_table = create_page_table();
    if (!root_page_table)
    {
        uart_puts("Error: no se pudo crear la tabla raiz\n");
        return;
    }
    uart_puts("Tabla raiz creada en: ");
    uart_puthex((uintptr_t)root_page_table);
    uart_puts("\n");

    // mapear el kernel
    extern uint8_t _kernel_start;
    extern uint8_t _kernel_end;

    uintptr_t kernel_start = (uintptr_t)&_kernel_start;
    uintptr_t kernel_end = (uintptr_t)&kernel_end;

    uart_puts("Mapeand kernel desde "); uart_puthex(kernel_start);
    uart_puts(" hasta "); uart_puthex(kernel_end);
    uart_puts("\n");

    // mapear cada pagina del kernel con mapeo de identidad
    for (uintptr_t addr = kernel_start; addr < kernel_end; addr += PAGE_SIZE) {
        map_page(root_page_table, addr, addr, PTE_KERNEL);
    }

    uart_puts("Mapeando perifericos...\n");
    map_page(root_page_table, 0x10000000, 0x10000000, PTE_KERNEL); //uart

    // activar la mmu
    uint64_t satp = (8ULL << 60) | ((uintptr_t)root_page_table >> 12);

    uart_puts("Escribiendo SATP: ");
    uart_puthex(satp);
    uart_puts("\n");

    // escribir en el reg de satp
    __asm__ volatile (
        "csrw satp, %0\n"
        "sfence.vma\n" // invalidar tlb
        :
        : "r"(satp)
        : "memory"
    );

    uart_puts("MMU activada en modo Sv39\n");

}