#include "../io/io.h"

#define IDT_ENTRIES 256

struct idt_entry 
  {
    unsigned short base_low;
    unsigned short segment;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_high;
  } __attribute__((packed));

static struct idt_entry idt[IDT_ENTRIES];

void int_handler()
{
  kprintf("Ein Interrupt!\n");
  while(1);
}

void set_gate_entry(unsigned char num, unsigned long base, unsigned short segment, unsigned char flags) 
{
  idt[num].base_high = (base & 0xFFFF);
  idt[num].base_low = (base >> 16) & 0xFFFF;

  idt[num].always0 = 0;
  idt[num].segment = segment;
  idt[num].flags = flags;
}

void load_idt(void)
{    
  struct {
    unsigned short limit;
    void* pointer;
  } __attribute__((packed)) idtp = {
    .limit = IDT_ENTRIES * 8 -1,
    .pointer = idt,
  };
  asm volatile("lidt %0" : : "m" (idtp));
  //asm volatile("sti");
}

void init_idt(void)
{
  set_gate_entry(0, (unsigned long) int_handler, 0x08, 0x8E);
  //set_gate_entry(4, (unsigned long) int_handler, 0x0a, 0x8E);
  load_idt();
}
