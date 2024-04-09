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
  //kprintf("d\n", 404); // \n does not work if % is used before
  kprintf("Hello World!\n");
  //kprintf("%d", 0x2A);

  //int e = 2 / 0;
}
