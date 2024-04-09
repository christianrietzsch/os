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
  //kprintf("Hello World!\n");
  //asm volatile("int $0x48");
  //kprintf("%d\n", 404); // \n does not work?
  //int test = 2 / 0;
  //asm volatile("int $0xAA");
  unsigned int test = 0xA;
  if(test <= 0x1f)
  {
    //kprintf("%d", test);
  }
  //kprintf("%d\n", 0x1f);
  //kprintf("Test");
  //asm volatile("int $0x48");
  int e = 2 / 0;
  //asm volatile("int $0x48");
}
