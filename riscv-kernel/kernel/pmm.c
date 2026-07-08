#include "pmm.h"
#include "../include/memory.h"
#include "uart.h"

#define TOTAL_PAGES (MEMORY_SIZE / PAGE_SIZE)
#define BITMAP_SIZE ((TOTAL_PAGES + 7) / 8)

static uint8_t bitmap[BITMAP_SIZE];

extern uint8_t _kernel_start;
extern uint8_t _kernel_end;

void pmm_init()
{
    for (size_t i = 0; i < BITMAP_SIZE; i++)
    {
        bitmap[i] = 0xFF;
    }

    uintptr_t kernel_start = (uintptr_t)&_kernel_start;
    uintptr_t kernel_end = (uintptr_t)&_kernel_end;

    uintptr_t start_page = (kernel_start - MEMORY_BASE) / PAGE_SIZE;
    uintptr_t num_pages = (kernel_end - kernel_start + PAGE_SIZE - 1) / PAGE_SIZE;

    uart_puts("start_page=");
    uart_puthex(start_page);
    uart_puts("\n");
    uart_puts("num_pages=");
    uart_puthex(num_pages);
    uart_puts("\n");

    for (uintptr_t i = start_page; i < start_page + num_pages; i++)
    {
        if (i < TOTAL_PAGES)
        {
            bitmap[i / 8] &= (uint8_t)~(1 << (i % 8));
        }
    }

    uart_puts("bitmap[0]=");
    uart_puthex(bitmap[0]);
    uart_puts("\n");
}

void *pmm_alloc_page()
{
    for (uintptr_t i = 0; i < TOTAL_PAGES; i++)
    {
        if (bitmap[i / 8] & (1 << (i % 8)))
        {
            bitmap[i / 8] &= ~(1 << (i % 8));
            return (void *)(MEMORY_BASE + i * PAGE_SIZE);
        }
    }
    return NULL;
}

void pmm_free_page(void *page)
{
    uintptr_t addr = (uintptr_t)page;
    if (addr < MEMORY_BASE || addr >= MEMORY_BASE + MEMORY_SIZE)
    {
        return;
    }
    uintptr_t page_index = (addr - MEMORY_BASE) / PAGE_SIZE;
    bitmap[page_index / 8] |= (1 << (page_index % 8));
}