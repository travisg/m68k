#include "intc.h"
#include "uart.h"

// simple test code for qemu 6.0's virt machine for 68k

void _main() {
    // initialize the uart before the int controller is brought up
    // so we can output something.
    uart_early_init();
    uart_puts("hello!\n");

    uart_put_hex(0x12345678);
    uart_puts("\n");

    intc_init();
    uart_init();

    uart_puts("fin.\n");

    for (;;);
}
