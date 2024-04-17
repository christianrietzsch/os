#include "libc/descriptors/descriptors.h"
#include "libc/io/io.h"
#include "libc/std/bool.h"

void init_descriptors()
{
  init_gdt();
  kprintf("Initialised GDT\n");
  init_pic();
  kprintf("Initialised PIC\n");
  init_idt();
  kprintf("Initialised IDT\n"); // \n funktioniert nicht ?
  //init_keyboard();
  // next : fix irqs and add keyboard handler in right position
}

void init(void)
{
  clear();
  init_descriptors();

  //#include "libc/io/keyboard.h"
  //send_command(0x10);
  //send_command(0x11);
  //clear();
  
  //kprintf("d\n", 404); // \n does not work if % is used before
  //kprintf("Hello World!\n");
  //asm volatile("int $0x91");
  //asm volatile("int $0x48");

  kprintf("%d", 0x2A);
  kprintf("Hello");

  boolean t = true;
  kprintf("%d", t);
}
