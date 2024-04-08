#include "../io/io.h"
#include "../types/types.h"

struct idt_entry {
  uint16_t base_lo;
  uint16_t sel;
  uint8_t always0;
  uint8_t flags;
  uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  idt[num].base_lo = base & 0xFFFF;
  idt[num].base_hi = (base >> 16) & 0xFFFF;
  idt[num].sel = sel;
  idt[num].base_lo = 0;
  idt[num].flags = flags;
}

void idt_load(uint32_t idt_address)
{
  asm volatile("lidt (%0)" : : "r" (idt_address));
}

void isr_handler()
{
  kprintf("Hello!\n");
  while(1);
  
}

void *memset(void *dest, char val, unsigned long long count)
{
  char *temp = (char*) dest;
  for(; count != 0; count--) *temp++ = val;
  return dest;
}

void init_idt(void) {
  idtp.limit = (sizeof(struct idt_entry) *256) -1;
  idtp.base = (uint32_t)&idt; //should be int?
  memset(&idt, 0, sizeof(struct idt_entry) * 256);
  idt_load((uint32_t)&idtp);
  idt_set_gate(0, (uint32_t)isr_handler, 0x08, 0x8E);
}
