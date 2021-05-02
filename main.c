#include "uart.h"

// simple test code for qemu 6.0's virt machine for 68k

void _main() {
    uart_init();
    uart_puts("hello, world\n");

    for (;;);
}
