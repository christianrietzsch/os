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
.extern fault_handler

.global _start
_start:
        mov $kernel_stack, %esp

        call init

_stop:
        cli
        hlt

        jmp _stop


.global _isr0
.global _isr1
.global _isr2
.global _isr3
.global _isr4
.global _isr5
.global _isr6
.global _isr7
.global _isr8
.global _isr9
.global _isr10
.global _isr11
.global _isr12
.global _isr13
.global _isr14
.global _isr15
.global _isr16
.global _isr17
.global _isr18
.global _isr19
.global _isr20
.global _isr21
.global _isr22
.global _isr23
.global _isr24
.global _isr25
.global _isr26
.global _isr27
.global _isr28
.global _isr29
.global _isr30
.global _isr31

_isr0:
        cli
        pushl $0
        pushl $0
        jmp isr_common_stub

_isr1:
        cli
        pushl $0
        pushl $1
        jmp isr_common_stub

_isr2:
        cli
        pushl $0
        pushl $2
        jmp isr_commmon_stub

_isr3:
        cli
        pushl $0
        pushl $3
        jmp isr_commmon_stub

_isr4:
        cli
        pushl $0
        pushl $4
        jmp isr_commmon_stub

_isr5:
        cli
        pushl $0
        pushl $5
        jmp isr_commmon_stub

_isr6:
        cli
        pushl $0
        pushl $6
        jmp isr_commmon_stub

_isr7:
        cli
        pushl $0
        pushl $7
        jmp isr_commmon_stub

_isr8:
        cli
        pushl $0
        pushl $8
        jmp isr_commmon_stub
        
_isr9:
        cli
        pushl $0
        pushl $9
        jmp isr_commmon_stub

_isr10:
        cli
        pushl $0
        pushl $10
        jmp isr_commmon_stub

_isr11:
        cli
        pushl $0
        pushl $11
        jmp isr_commmon_stub

_isr12:
        cli
        pushl  $0
        pushl $12
        jmp isr_commmon_stub

_isr13:
        cli
        pushl $0
        pushl $14
        jmp isr_commmon_stub

_isr15:
        cli
        pushl $0
        pushl $16
        jmp isr_commmon_stub

_isr17:
        cli
        pushl $0
        pushl $17
        jmp isr_commmon_stub

_isr18:
        cli
        pushl $0
        pushl $18
        jmp isr_commmon_stub

_isr19:
        cli
        pushl $0
        pushl $19
        jmp isr_commmon_stub

_isr20:
        cli
        pushl $0
        pushl $20
        jmp isr_commmon_stub

_isr21:
        cli
        pushl $0
        pushl $21
        jmp isr_commmon_stub

_isr22:
        cli
        pushl $0
        pushl $22
        jmp isr_commmon_stub

_isr23:
        cli
        pushl $0
        pushl $23
        jmp isr_commmon_stub

_isr24:
        cli
        pushl $0
        pushl $24
        jmp isr_commmon_stub

_isr25:
        cli
        pushl $0
        pushl $25
        jmp isr_commmon_stub

_isr26:
        cli
        pushl $0
        pushl $26
        jmp isr_commmon_stub

_isr27:
        cli
        pushl $0
        pushl $27
        jmp isr_commmon_stub

_isr28:
        cli
        pushl $0
        pushl $28
        jmp isr_commmon_stub

_isr29:
        cli
        pushl $0
        pushl $29
        jmp isr_commmon_stub

_isr30:
        cli
        pushl $0
        pushl  $30
        jmp isr_commmon_stub

_isr31:
        cli
        pushl $0
        pushl $31
        jmp isr_commmon_stub

isr_common_stub:
        push %ebp
        push %edi      
        push %esi      
        push %edx      
        push %ecx      
        push %ebx      
        push %eax      

        push %esp
        add $4, %esp
        call fault_handler

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
