ENTRY(_start)

SECTIONS
{
    . = 0x100000;  /* Kernel'in yükleneceği adres */
    
    .text :
    {
        *(.multiboot)
        *(.text)
    }

    .rodata :
    {
        *(.rodata)
    }

    .data :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
}
