.section multiboot

#define MB_MAGIC 0x1badb002
#define MB_FLAGS 0x0
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)

.align 4
.int MB_MAGIC
.int MB_FLAGS
.int MB_CHECKSUM

.section .text
.extern init

.global _start
_start:
        mov $kernel_stack, %esp

        call init

_stop:
        cli
        hlt

        jmp _stop

.macro intr_stub nr
.global intr_stub_\nr
intr_stub_\nr:
        pushl $0
        pushl $\nr
        jmp intr_common_handler
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

intr_stub 32
intr_stub 33
intr_stub 34
intr_stub 35
intr_stub 36
intr_stub 37
intr_stub 38
intr_stub 39
intr_stub 40
intr_stub 41
intr_stub 42
intr_stub 43
intr_stub 44
intr_stub 45
intr_stub 46
intr_stub 47

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
        add $4, %esp

        pop %eax
        pop %ebx
        pop %ecx
        pop %edx
        pop %esi
        pop %edi
        pop %ebp

        add $8, %esp

        iret

.section .bss
.space 8192
kernel_stack:
