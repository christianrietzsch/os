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
  //asm volatile("int $0x48");
  //int test = 2 / 0;
  //asm volatile("int $0x4");
  kprintf("Test");
}
