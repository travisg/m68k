#include "intc.h"

#include "uart.h"
#include "virt.h"

enum {
    REG_STATUS          = 0x00,
    REG_IRQ_PENDING     = 0x04,
    REG_IRQ_DISABLE_ALL = 0x08,
    REG_DISABLE         = 0x0c,
    REG_ENABLE          = 0x10,
};

static volatile unsigned int *pic_base(unsigned int n) {
    if (n < 0 || n > 6)
        return 0;

    return (volatile unsigned int *)(VIRT_GF_PIC_MMIO_BASE + 0x1000 * n);
}

static void pic_write(unsigned int pic, unsigned int reg, unsigned int val) {
    pic_base(pic)[reg / 4] = val;
}

static unsigned int pic_read(unsigned int pic, unsigned int reg) {
    return pic_base(pic)[reg / 4];
}

void intc_init(void) {
    // initialize all of the irq controllers to 0
    for (int i = 0; i < 6; i++) {
        pic_write(i, REG_IRQ_DISABLE_ALL, 0);
    }
}
