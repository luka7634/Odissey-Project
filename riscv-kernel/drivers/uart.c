#include "uart.h"
#include "board.h"

static inline void uart_wait_tx_ready(void)
{
    while (!(*((volatile unsigned char *)(UART_BASE + UART_LSR)) & UART_LSR_THRE))
    {
        // busy wait
    }
}

void uart_init(void)
{
    // init uart, empty 4 now
}

void uart_putc(char c)
{
    uart_wait_tx_ready();
    *((volatile unsigned char *)(UART_BASE + UART_THR)) = c; // write the byte
}

void uart_puts(const char *str)
{
    while (*str)
    {
        uart_putc(*str++);
    }
}

void uart_puthex(unsigned long long num)
{
    uart_puts("0x");
    if (num == 0)
    {
        uart_putc('0');
        return;
    }

    char hex[16];
    int i = 0;
    while (num > 0)
    {
        int digit = num & 0xF;
        if (digit < 10)
            hex[i++] = '0' + digit;
        else
            hex[i++] = 'A' + (digit - 10);

        num >>= 4;
    }

    while (i > 0)
    {
        uart_putc(hex[--i]);
    }
}