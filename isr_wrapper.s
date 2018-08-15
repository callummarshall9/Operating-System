/* filename: isr_wrapper.s */
.global   isr_wrapper
.align   4
 .extern interrupt_handler

isr_wrapper:
    pushal
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    call interrupt_handler
    popal
    iret
