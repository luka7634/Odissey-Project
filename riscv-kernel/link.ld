OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS {
    . = 0x80000000;

    _kernel_start = .;

    .text : {
        *(.text)
    }

    . = ALIGN(4);
    .rodata : {
        *(.rodata)
    }

    . = ALIGN(4);
    .data : {
        *(.data)
    }

    . = ALIGN(4);
    _bss_start = .;
    .bss : {
        *(.bss)
    }
    _bss_end = .;

    _kernel_end = .;
}