#include "../types/types.h"
#include "io.h"
#include "serial.h"

static void send_command(uint8_t command);

void init_keyboard(void)
{

  while (inb(0x64) & 0x1)
  {
    inb(0x60);
  }

  send_command(0xF4);
}

static void send_command(uint8_t command)
{
  while((inb(0x64) & 0x2)) {}
  outb(0x60, command);
}

uint8_t translate_scancode(int set, uint16_t scancode);

void irq_handler(uint8_t irq)
{
  uint8_t scancode;
  uint8_t keycode = 0;
  int break_code = 0;

  static int e0_code = 0;
  static int e1_code = 0;
  static uint16_t e1_prev = 0;

  scancode = inb(0x60);
  if((scancode & 0x80) && 
     (e1_code || (scancode != 0xE1)) &&
     (e0_code || (scancode != 0xE0)))
  {
    break_code = 1;
    scancode &= ~0x80;
  }

  if(e0_code)
  {
    if((scancode == 0x2A) || (scancode == 0x36))
    {
      e0_code = 0;
      return;
    }

    keycode = translate_scancode(1, scancode);
    e0_code = 0;
  } else if(e1_code == 2)
    {
      e1_prev |= ((uint16_t) scancode <<8);
      keycode = translate_scancode(2, e1_prev);
      e1_code = 0;
  } else if(e1_code == 1)
    {
      e1_prev = scancode;
      e1_code++;
  } else if(scancode == 0xE0)
    {
      e0_code = 1;
  } else if(scancode == 0xE1)
    {
      keycode = translate_scancode(1, scancode);
  }
  kprintf("%c", keycode);
}

uint8_t translate_scancode(int set, uint16_t scancode)
{
  uint8_t kbdus[128] = 
  {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '’', 0, 
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*',
    0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0,
    0, 0, 0
  };
  return kbdus[scancode];
}
