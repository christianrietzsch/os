#include "../io/io.h"
#include "../types/types.h"

#define IDT_ENTRIES 256

extern void intr_stub_0(void);
extern void intr_stub_1(void);
extern void intr_stub_2(void);
extern void intr_stub_3(void);
extern void intr_stub_4(void);
extern void intr_stub_5(void);
extern void intr_stub_6(void);
extern void intr_stub_7(void);
extern void intr_stub_8(void);
extern void intr_stub_9(void);
extern void intr_stub_10(void);
extern void intr_stub_11(void);
extern void intr_stub_12(void);
extern void intr_stub_13(void);
extern void intr_stub_14(void);
extern void intr_stub_15(void);
extern void intr_stub_16(void);
extern void intr_stub_17(void);
extern void intr_stub_18(void);
extern void intr_stub_32(void);
extern void intr_stub_33(void);
extern void intr_stub_34(void);
extern void intr_stub_35(void);
extern void intr_stub_36(void);
extern void intr_stub_37(void);
extern void intr_stub_38(void);
extern void intr_stub_39(void);
extern void intr_stub_40(void);
extern void intr_stub_41(void);
extern void intr_stub_42(void);
extern void intr_stub_43(void);
extern void intr_stub_44(void);
extern void intr_stub_45(void);
extern void intr_stub_46(void);
extern void intr_stub_47(void);
extern void intr_stub_48(void);

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

void handle_interrupt(struct cpu_state* cpu)
{
  if(cpu->intr <= 0x1f)
  {
    kprintf("Exception: %d, Kernel angehalten!\n", cpu->intr);

    while(1)
    {
      asm volatile("cli; hlt");
    }
  }
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
  set_gate_entry(0, (uint32_t) intr_stub_0, 0x0a, 0x8E);
  set_gate_entry(1, (uint32_t) intr_stub_1, 0x0a, 0x8E);
  set_gate_entry(2, (uint32_t) intr_stub_2, 0x0a, 0x8E);
  set_gate_entry(3, (uint32_t) intr_stub_3, 0x0a, 0x8E);
  set_gate_entry(4, (uint32_t) intr_stub_4, 0x0a, 0x8E);
  set_gate_entry(5, (uint32_t) intr_stub_5, 0x0a, 0x8E);
  set_gate_entry(6, (uint32_t) intr_stub_6, 0x0a, 0x8E);
  set_gate_entry(7, (uint32_t) intr_stub_7, 0x0a, 0x8E);
  set_gate_entry(8, (uint32_t) intr_stub_8, 0x0a, 0x8E);
  set_gate_entry(9, (uint32_t) intr_stub_9, 0x0a, 0x8E);
  set_gate_entry(10, (uint32_t) intr_stub_10, 0x0a, 0x8E);
  set_gate_entry(11, (uint32_t) intr_stub_11, 0x0a, 0x8E);
  set_gate_entry(12, (uint32_t) intr_stub_12, 0x0a, 0x8E);
  set_gate_entry(13, (uint32_t) intr_stub_13, 0x0a, 0x8E);
  set_gate_entry(14, (uint32_t) intr_stub_14, 0x0a, 0x8E);
  set_gate_entry(15, (uint32_t) intr_stub_15, 0x0a, 0x8E);
  set_gate_entry(16, (uint32_t) intr_stub_16, 0x0a, 0x8E);
  set_gate_entry(17, (uint32_t) intr_stub_17, 0x0a, 0x8E);
  set_gate_entry(18, (uint32_t) intr_stub_18, 0x0a, 0x8E);
  set_gate_entry(32, (uint32_t) intr_stub_32, 0x0a, 0x8E);
  set_gate_entry(33, (uint32_t) intr_stub_33, 0x0a, 0x8E);
  //set_gate_entry(34, (uint32_t) intr_stub_34, 0x0a, 0x8E);
  //set_gate_entry(35, (uint32_t) intr_stub_35, 0x0a, 0x8E);
  //set_gate_entry(36, (uint32_t) intr_stub_36, 0x0a, 0x8E);
  //set_gate_entry(37, (uint32_t) intr_stub_37, 0x0a, 0x8E);
  //set_gate_entry(38, (uint32_t) intr_stub_38, 0x0a, 0x8E);
  //set_gate_entry(39, (uint32_t) intr_stub_39, 0x0a, 0x8E);
  //set_gate_entry(40, (uint32_t) intr_stub_40, 0x0a, 0x8E);
  //set_gate_entry(41, (uint32_t) intr_stub_41, 0x0a, 0x8E);
  //set_gate_entry(42, (uint32_t) intr_stub_42, 0x0a, 0x8E);
  //set_gate_entry(43, (uint32_t) intr_stub_43, 0x0a, 0x8E);
  //set_gate_entry(44, (uint32_t) intr_stub_44, 0x0a, 0x8E);
  //set_gate_entry(45, (uint32_t) intr_stub_45, 0x0a, 0x8E);
  //set_gate_entry(46, (uint32_t) intr_stub_46, 0x0a, 0x8E);
  //set_gate_entry(47, (uint32_t) intr_stub_47, 0x0a, 0x8E);
  set_gate_entry(48, (uint32_t) intr_stub_48, 0x0a, 0x8E);
  load_idt();
}
