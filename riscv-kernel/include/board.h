#ifndef BOARD_H
    #define BOARD_H

#define UART_BASE 0x10000000 // direccion base de uart
// offsets de los registros
#define UART_THR 0x00          // transmit holding reg
#define UART_LSR 0x05          // line status reg
#define UART_LSR_THRE (1 << 5) // lsr bit 5 mask

#endif