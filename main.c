/*
  from qemu's info mtree for machine mcf5208evb
  0000000000000000-ffffffffffffffff (prio 0, i/o): system
    0000000000000000-00000000001fffff (prio 0, rom): mcf5208.rom
    0000000040000000-0000000047ffffff (prio 0, ram): mcf5208.ram
    0000000080000000-0000000080003fff (prio 0, ram): mcf5208.sram
    00000000fc030000-00000000fc0303ff (prio 0, i/o): fec
    00000000fc048000-00000000fc0480ff (prio 0, i/o): mcf
    00000000fc060000-00000000fc06003f (prio 0, i/o): uart
    00000000fc064000-00000000fc06403f (prio 0, i/o): uart
    00000000fc068000-00000000fc06803f (prio 0, i/o): uart
    00000000fc080000-00000000fc083fff (prio 0, i/o): m5208-timer
    00000000fc084000-00000000fc087fff (prio 0, i/o): m5208-timer
    00000000fc0a8000-00000000fc0abfff (prio 0, i/o): m5208-sys
*/

static volatile unsigned int *uart_base = (void *)0xfc060000;

enum uart_regs {
    UART_MR = 0,
    UART_CSR,
    UART_CMD,
    UART_BUF,
    UART_ACR,
    UART_IMR
};

static void uart_putc(char c) {
    uart_base[UART_BUF] =  c;
}

static void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s);
        s++;
    }
}

static void uart_init(void) {
    uart_base[UART_CMD] = (1 << 2); // enable transmitter
}

void _main() {
    uart_puts("hello, world\n");

    for (;;);
}
