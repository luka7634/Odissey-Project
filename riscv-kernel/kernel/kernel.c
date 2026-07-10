#include "uart.h"
#include "pmm.h"
#include "vmm.h"

void kmain()
{
    uart_init();
    uart_puts("--- KERNEL INICIADO ---\n");
    uart_puts("iniciando pmm...\n");
    pmm_init();
    uart_puts("pmm inicializado :D\n");

    uart_puts("inicializando vmm...\n");
    vmm_init();
    
    uart_puts("Sitema lito, entrando en bucle infinito :D\n");

    while (1)
        ;
}