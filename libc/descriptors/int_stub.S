.macro intr_stub nr
.global intr_stub_\nr
intr_stub_\nr:
        pushl $0
        pushl $\nr
        jmp intr_common_handler
.endm

.macro irq nr
.global irq\nr
irq\nr:
        pushl $\nr
        pushl $(\nr+32)
        jmp irq_common_stub
.endm

.macro intr_stub_error_code nr
.global intr_stub_\nr
intr_stub_\nr:
        pushl $\nr
        jmp intr_common_handler
.endm

intr_stub 0
intr_stub 1
intr_stub 2
intr_stub 3
intr_stub 4
intr_stub 5
intr_stub 6
intr_stub 7
intr_stub_error_code 8
intr_stub 9
intr_stub_error_code 10
intr_stub_error_code 11
intr_stub_error_code 12
intr_stub_error_code 13
intr_stub_error_code 14
intr_stub 15
intr_stub 16
intr_stub_error_code 17
intr_stub 18

irq 0       
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15

intr_stub 48

.extern handle_interrupt
intr_common_handler:
        push %ebp
        push %edi
        push %esi
        push %edx
        push %ecx
        push %ebx
        push %eax

        push %esp
        call handle_interrupt       
        mov %eax, %esp

        pop %eax
        pop %ebx
        pop %ecx
        pop %edx
        pop %esi
        pop %edi
        pop %ebp


        add $8, %esp

        iret

.extern irq_handler
irq_common_stub:
        push %ebp
        push %edi
        push %esi
        push %edx
        push %ecx
        push %ebx
        push %eax

        push %esp
        call irq_handler
        mov %eax, %esp

        pop %eax
        pop %ebx
        pop %ecx
        pop %edx
        pop %esi
        pop %edi
        pop %ebp


        add $8, %esp

        iret
