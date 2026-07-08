
OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS {
    . = 0x80000000;

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    /* Definimos los símbolos para la BSS */
    _bss_start = .;
    .bss : {
        *(.bss)
    }
    _bss_end = .;
}