.section .text.startup
.globl _start
_start:
    // clear bss
    lea     __bss_start,%a0
    cmpal   #_end,%a0
    beqs    1f
0:
    clrb    %a0@+
    cmpal   #_end,%a0
    bnes    0b
1:

    movel   #_stack_top,%sp
    bsr     _main
    jmp     .

.bss
.align 8
_stack_base:
    .skip 4096
_stack_top:
