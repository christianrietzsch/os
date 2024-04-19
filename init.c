#include "libc/descriptors/descriptors.h"
#include "libc/io/io.h"
#include "libc/io/keyboard.h"

void init_descriptors()
{
  init_gdt();
  kprintf("[Info]: Initialised GDT\n");
  init_pic();
  kprintf("[Info]: Initialised PIC\n");
  init_idt();
  kprintf("[Info]: Initialised IDT\n");
  init_keyboard();
  kprintf("[Info]: Initialised Keyboard\n");
  kprintf("\n\n");
}

void info(const char* msg)
{
  kprintf("[Info]: %s\n", msg);
}

void init(void)
{
  clear();
  init_descriptors();
  

  while(1) {}
      
  kprintf("[ERROR]: Kernel stopped!");
}
