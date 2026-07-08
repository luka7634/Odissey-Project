#include "uart.h"

void kmain()
{
    uart_init();
    uart_puts("Holaaaaaaaaaaa\n");
    uart_puthex(0xFF);
    uart_putc('\n');
    while (1)
        ;
}