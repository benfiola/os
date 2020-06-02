.section .data
_test_message:
    .string "bios_function called"


.section .text
.global bios_function
.type bios_function, @function
bios_function:
    push %ebp
    mov %esp, %ebp

    push $_test_message
    call Terminal_writeString

    mov %ebp, %esp
    pop %ebp
    ret

.section .text
enter_real_mode:


.section .text
leave_real_mode:


