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
  init_descriptors();
  clear();
  kprintf("Hello World!\n");
  //kprintf("%d\n", 404); // \n does not work?
  //int e = 2 / 0;
  asm volatile("int $0x48");
}
