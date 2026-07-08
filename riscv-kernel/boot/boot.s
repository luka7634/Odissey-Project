.section .text
.global _start

_start:
    li sp, 0x80000000 + 0x100000

    la t0, _bss_start
    la t1, _bss_end

bss_clear_loop:
    beq t0, t1, bss_clear_done
    sw zero, 0(t0)

    addi t0, t0, 4

    j bss_clear_loop

bss_clear_done:
    call kmain

hang:
    j hang
