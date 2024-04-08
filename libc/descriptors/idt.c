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

void int_handler()
{
  kprintf("Ein Interrupt!\n");
  while(1);
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
  set_gate_entry(0, (uint32_t) int_handler, 0x0a, 0x8E);
  set_gate_entry(4, (uint32_t) int_handler, 0x0a, 0x8E);
  kprintf("Loading idt...");
  load_idt();
  kprintf("done loading idt");
}
