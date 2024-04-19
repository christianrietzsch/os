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
  // next : fix irqs and add keyboard handler in right position
}

void info(const char* msg)
{
  kprintf("[Info]: %s\n", msg);
}

void init(void)
{
  clear();
  init_descriptors();
  //send_command(0x03);
  //clear();
  
  //kprintf("d\n", 404); // \n does not work if % is used before
  //kprintf("Hello World!\n");
  //asm volatile("int $0x91");
  //asm volatile("int $0x48");

  //kprintf("%d", 0x2A);
  //kprintf("Hello");

  //boolean t = true;
  //kprintf("\n%d", t);
  //info("Test"); 
  //kprintf("E");

  while(1) {    
  }
  
//  unsigned char c;
//  unsigned char last = ' ';
//    
//    c = inb(0x60);    
//    if(c != last) 
//    {
//    kprintf("%c", c);
//    last = c;
//    }
//
//  // funktioniert nicht, da irq33 nicht aufgerufen wird
  // }

    
  kprintf("[ERROR]: Kernel stopped!");
}
