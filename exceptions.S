.text
.align 4
_m68k_illegal_exc:
    stop #0
    jmp _m68k_illegal_exc

.data
.align 4
.globl m68k_vector_base
m68k_vector_base:
.org 0x10
    .long _m68k_illegal_exc
.org 256 * 4
m68k_vector_top:

