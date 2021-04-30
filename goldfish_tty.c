#include "goldfish_tty.h"

// goldfish tty
// from qemu/hw/char/goldfish_tty.c
volatile unsigned int *goldfish_tty_base = 0xff008000;

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
    goldfish_tty_base[REG_PUT_CHAR] = c;
}

void uart_init(void) { }

void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s);
        s++;
    }
}


