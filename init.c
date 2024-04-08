#include "libc/descriptors/descriptors.h"
#include "libc/io/io.h"

void init_descriptors()
{
  init_gdt();
  init_idt();
  init_pic();
}

void init(void)
{
  clear();
  init_descriptors();
  kprintf("Hello World!\n");
  asm volatile("int $0x0");
  kprintf("Test");
}
