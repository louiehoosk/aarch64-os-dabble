.global _start
_start:
    ldr x30, =__stack_base
    mov sp, x30
    bl kmain
    b .
