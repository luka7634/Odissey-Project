#include "uart.h"
#include "pmm.h"

void kmain()
{
    uart_init();
    uart_puts("Holaaaaaaaaaaaaa :D\n");
    uart_puts("iniciando pmm...\n");
    pmm_init();
    uart_puts("pmm inicializado :D\n");

    // probar asignacion/liberacion
    void *page = pmm_alloc_page();
    if (page)
    {
        uart_puts("pagina asignada en: ");
        uart_puthex((uintptr_t)page);
        uart_puts("\n");
        pmm_free_page(page);
        uart_puts("pagina liberada :D\n");
    }
    else
    {
        uart_puts("ERROR: No hay paginas libres!\n");
    }

    while (1)
        ;
}