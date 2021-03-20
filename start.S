.globl _start
_start:
    movel   #_stack_top,%sp
    bsr     _main
    jmp     .

.data
.align 2
_stack_base:
    .skip 4096
_stack_top:
