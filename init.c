#include "libc/descriptors/descriptors.h"
#include "libc/io/io.h"

void init_descriptors()
{
  init_gdt();
  init_idt();
  //init_pic();
  //should only be activated when the idt works
}

void init(void)
{
  clear();
  init_descriptors();
  kprintf("Hello World!\n");
  asm volatile("int $0x0");
  kprintf("Test");
}
