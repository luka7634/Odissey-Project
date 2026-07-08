#ifndef UART_H
#define UART_H

#define UART_BASE 0x10000000 // direccion base de uart
// offsets de los registros
#define UART_THR 0x00          // transmit holding reg
#define UART_LSR 0x05          // line status reg
#define UART_LSR_THRE (1 << 5) // lsr bit 5 mask

void uart_init(void);

void uart_putc(char c);

void uart_puts(const char *str);

void uart_puthex(unsigned long long num);

#endif
