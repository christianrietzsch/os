#include "../io/io.h"
#include "../types/types.h"

#define IDT_ENTRIES 256

struct idt_entry 
  {
    uint16_t base_low;
    uint16_t segment;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
  } __attribute__((packed));

static struct idt_entry idt[IDT_ENTRIES];

struct cpu_state 
  {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;

    uint32_t intr;
    uint32_t error;

    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
  };

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void fault_handler(struct cpu_state* cpu)
{ 
  kprintf("EXCEPTION: %d", cpu->intr);
}

void set_gate_entry(uint8_t num, uint32_t base, uint16_t segment, uint8_t flags) 
{
  idt[num].base_low = (base & 0xFFFF);
  idt[num].base_high = (base >> 16) & 0xFFFF;

  idt[num].always0 = 0;
  idt[num].segment = segment;
  idt[num].flags = flags;
}

void load_idt(void)
{    
  struct {
    uint16_t limit;
    void* pointer;
  } __attribute__((packed)) idtp = {
    .limit = IDT_ENTRIES * 8 -1,
    .pointer = idt,
  };
  asm volatile("lidt %0" : : "m" (idtp));
}

void init_idt(void)
{
  set_gate_entry(0, (uint32_t) isr0, 0x0a, 0x8E);
  set_gate_entry(1, (uint32_t) isr1, 0x0a, 0x8E);
  set_gate_entry(2, (uint32_t) isr2, 0x0a, 0x8E);
  set_gate_entry(3, (uint32_t) isr3, 0x0a, 0x8E);
  set_gate_entry(4, (uint32_t) isr4, 0x0a, 0x8E);
  set_gate_entry(5, (uint32_t) isr5, 0x0a, 0x8E);
  set_gate_entry(6, (uint32_t) isr6, 0x0a, 0x8E);
  set_gate_entry(7, (uint32_t) isr7, 0x0a, 0x8E);
  set_gate_entry(8, (uint32_t) isr8, 0x0a, 0x8E);
  set_gate_entry(9, (uint32_t) isr9, 0x0a, 0x8E);
  set_gate_entry(10, (uint32_t) isr10, 0x0a, 0x8E);
  set_gate_entry(11, (uint32_t) isr11, 0x0a, 0x8E);
  set_gate_entry(12, (uint32_t) isr12, 0x0a, 0x8E);
  set_gate_entry(13, (uint32_t) isr13, 0x0a, 0x8E);
  set_gate_entry(14, (uint32_t) isr14, 0x0a, 0x8E);
  set_gate_entry(15, (uint32_t) isr15, 0x0a, 0x8E);
  set_gate_entry(16, (uint32_t) isr16, 0x0a, 0x8E);
  set_gate_entry(17, (uint32_t) isr17, 0x0a, 0x8E);
  set_gate_entry(18, (uint32_t) isr18, 0x0a, 0x8E);
  set_gate_entry(19, (uint32_t) isr19, 0x0a, 0x8E);
  set_gate_entry(20, (uint32_t) isr20, 0x0a, 0x8E);
  set_gate_entry(21, (uint32_t) isr21, 0x0a, 0x8E);
  set_gate_entry(22, (uint32_t) isr22, 0x0a, 0x8E);
  set_gate_entry(23, (uint32_t) isr23, 0x0a, 0x8E);
  set_gate_entry(24, (uint32_t) isr24, 0x0a, 0x8E);
  set_gate_entry(25, (uint32_t) isr25, 0x0a, 0x8E);
  set_gate_entry(26, (uint32_t) isr26, 0x0a, 0x8E);
  set_gate_entry(27, (uint32_t) isr27, 0x0a, 0x8E);
  set_gate_entry(28, (uint32_t) isr28, 0x0a, 0x8E);
  set_gate_entry(29, (uint32_t) isr29, 0x0a, 0x8E);
  set_gate_entry(30, (uint32_t) isr30, 0x0a, 0x8E);
  set_gate_entry(31, (uint32_t) isr31, 0x0a, 0x8E);
  load_idt();
}
