#include "uart.h"

#include "virt.h"

// goldfish tty
// from qemu/hw/char/goldfish_tty.c
volatile unsigned int * const goldfish_tty_base = (void *)VIRT_GF_TTY_MMIO_BASE;

// registers
enum {
    REG_PUT_CHAR      = 0x00,
    REG_BYTES_READY   = 0x04,
    REG_CMD           = 0x08,
    REG_DATA_PTR      = 0x10,
    REG_DATA_LEN      = 0x14,
    REG_DATA_PTR_HIGH = 0x18,
    REG_VERSION       = 0x20,
};

// commands

enum {
    CMD_INT_DISABLE   = 0x00,
    CMD_INT_ENABLE    = 0x01,
    CMD_WRITE_BUFFER  = 0x02,
    CMD_READ_BUFFER   = 0x03,
};

void uart_putc(char c) {
    goldfish_tty_base[REG_PUT_CHAR/4] = c;
}

void uart_early_init(void) { }
void uart_init(void) { }

void uart_puts(const char *s) {
    if (1) {
        // one character at a time version
        while (*s) {
            uart_putc(*s);
            s++;
        }
    } else {
        // use the CMD_WRITE_BUFFER routine
        goldfish_tty_base[REG_DATA_PTR/4] = (unsigned int)s;
        goldfish_tty_base[REG_DATA_PTR_HIGH/4] = 0;
        unsigned int len = 0;
        while (*s) {
            s++;
            len++;
        }
        goldfish_tty_base[REG_DATA_LEN/4] = len;
        goldfish_tty_base[REG_CMD/4] = CMD_WRITE_BUFFER;
    }
}

void uart_put_hex(unsigned int x) {
    const char * const hex = "0123456789abcdef";
    uart_putc('0');
    uart_putc('x');

    for (int i = 7; i >= 0; i--) {
        uart_putc(hex[(x >> (4 * i)) & 0xf]);
    }
}

