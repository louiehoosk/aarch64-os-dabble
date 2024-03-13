ENTRY(_start)
MEMORY {
    rom (rx!w) : ORIGIN = 0x40100000, LENGTH = 16K
    ram (rw!x) : ORIGIN = 0x40200000, LENGTH = 256K
}
SECTIONS {
    . = 0x40100000; /* RAM starts at 0x40000000 but if we ask to load the kernel there, QEMU will not load a DTB */
    __startup = .;
    .startup . : { boot.o(.text) } > rom
    .text : { *(.text) } > rom

    __ramrom = .;

    .bss : { *(.bss COMMON) } > ram
    .data : { *(.data) } > ram

    .stack : {
        . = ALIGN(8);
	__stack_top = .;
	FILL(0x0);
        . += 0x10000; /* 4kB of stack memory */
        __stack_base = .;
    } > ram
    .heap : {
    	. = ALIGN(8);
	__heap_base = .;
        FILL(0x0);
	. += 0x10000;
        __heap_top = .;
    } > ram
}

