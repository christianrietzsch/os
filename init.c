#include "libc/descriptors/descriptors.h"
#include "libc/io/io.h"

void init_descriptors()
{
  init_gdt();
  init_idt();
  init_pic();
}

void task_a(void) 
{
  while(1)
  {
    kprintf("A");
  }
}

void task_b(void)
{
  while(1)
  {
    kprintf("B");
  }
}

void init(void)
{
  init_descriptors();
  //asm volatile("int $0x0");
  clear();

}
