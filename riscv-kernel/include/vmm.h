#ifndef VMM_H
#define VMM_H

#include <stdint.h>
#include <stddef.h>

#define KERNEL_VIRT_BASE 0x80000000 // virtual kernel dir
#define KERNEL_PHYS_BASE 0x80000000 // physical kernel dir

#define PAGE_SIZE 4096

#define PT_LEVELS 3
#define PT_ENTRIES 512

// Flags of entries
#define PTE_VALID   (1 << 0)   // Valid
#define PTE_READ    (1 << 1)   // Read
#define PTE_WRITE   (1 << 2)   // Write
#define PTE_EXEC    (1 << 3)   // Exec
#define PTE_USER    (1 << 4)   // User Acces
#define PTE_GLOBAL  (1 << 5)   // Global
#define PTE_ACCESS  (1 << 6)   // accessed (hardware)
#define PTE_DIRTY   (1 << 7)   // modified (hardware)

#define PTE_KERNEL (PTE_VALID | PTE_READ | PTE_WRITE | PTE_EXEC | PTE_GLOBAL)
#define PTE_USER   (PTE_VALID | PTE_READ | PTE_WRITE | PTE_EXEC | PTE_USER)

#define PTE_ADDR_MASK 0x000FFFFFFFFFF000  // 54 bits mask for physical direction

#define PTE_PFN(addr) ((addr) >> 12) // physical page number

void vmm_init(void);

#endif