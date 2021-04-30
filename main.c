// simple test code for qemu 6.0's virt machine for 68k

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

static void uart_putc(char c) {
    goldfish_tty_base[REG_PUT_CHAR] = c;
}

static void uart_init(void) { }

static void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s);
        s++;
    }
}

void _main() {
    uart_puts("hello, world\n");

    for (;;);
}
