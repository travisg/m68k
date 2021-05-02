#include "intc.h"
#include "uart.h"

// simple test code for qemu 6.0's virt machine for 68k
extern void m68k_vector_base(void);

static void cpu_early_init(void) {
    // initialize critical cpu stuff
    asm("movec %0,%/vbr" :: "r"(&m68k_vector_base));
}

void _main() {
    cpu_early_init();

    // initialize the uart before the int controller is brought up
    // so we can output something.
    uart_early_init();
    uart_puts("hello!\n");

    uart_put_hex(0x12345678);
    uart_puts("\n");

    intc_init();
    uart_init();

    uart_puts("fin.\n");

    asm("illegal");

    for (;;);
}
