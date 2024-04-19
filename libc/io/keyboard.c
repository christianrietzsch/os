#include "../types/types.h"
#include "io.h"
#include "serial.h"
#include "../std/bool.h"

static void send_command(uint8_t command);

boolean shift = false;
boolean caps = false;

void init_keyboard(void)
{

  while (inb(0x64) & 0x1)
  {
    for(int i = 0; i< 10; i++)
    {
      inb(0x60);
    }
  }

  send_command(0xF4);
}

static void send_command(uint8_t command)
{
  while((inb(0x64) & 0x2)) {}
  outb(0x60, command);
}

void print_modifier(const char* s_normal, const char* s_shift)
{
    if(shift || caps)
    {
       kprintf("%s", s_shift);
    } else
      {
         kprintf("%s", s_normal);
      }
}

void print_letter(uint8_t scancode)
{
  switch (scancode)
  {
    case 0x0:
        kprintf("ERROR");
        break;
    case 0x1:
        kprintf("ESC");
        break;
    case 0x2:
        print_modifier("1", "!");
        break;
    case 0x3:
        print_modifier("2", "\"");
        break;
    case 0x4:
        print_modifier("3", "§");
        break;
    case 0x5:
        print_modifier("4", "$");
        break;
    case 0x6:
        print_modifier("5", "%");
        break;
    case 0x7:
        print_modifier("6", "&");
        break;
    case 0x8:
        print_modifier("/", "7");
        break;
    case 0x9:
        print_modifier("8", "(");
        break;
    case 0xA:
        print_modifier("9", ")");
        break;
    case 0xB:
        print_modifier("0", "=");
        break;
    case 0xC:
        print_modifier("ss", "SS");
        break;
     case 0xD:
        print_modifier("'", "`");
        break;
     case 0xE:
        del_last();
        break;
     case 0xF:
        kprintf("\t");
        break;
     case 0x10:
        print_modifier("q", "Q");
        break;
     case 0x11:
        print_modifier("w", "W");
        break;
     case 0x12:
        print_modifier("e", "E");
        break;
     case 0x13:
        print_modifier("r", "R");
        break;
     case 0x14:
        print_modifier("t", "t");
        break;
     case 0x15:
        print_modifier("z", "Z");
        break;
     case 0x16:
        print_modifier("u", "U");
        break;
     case 0x17:
        print_modifier("i", "I");
        break;
     case 0x18:
        print_modifier("o", "O");
        break;
     case 0x19:
        print_modifier("p", "P");
        break;
     case 0x1A:
        print_modifier("ue", "UE");
        break;
     case 0x1B:
        print_modifier("+", "*");
        break;
     case 0x1C:
        kprintf("\n");
        break;
     case 0x1D:
        kprintf("LEFT CTRL");
        break;
     case 0x1E:
        print_modifier("a", "A");
        break;
     case 0x1F:
        print_modifier("s", "S");
        break;
     case 0x20:
        print_modifier("d", "D");
        break;
     case 0x21:
        print_modifier("f", "F");
        break;
     case 0x22:
        print_modifier("g", "G");
        break;
     case 0x23:
        print_modifier("h", "H");
        break;
     case 0x24:
        print_modifier("j", "J");
        break;
     case 0x25:
        print_modifier("k", "K");
        break;
     case 0x26:
        print_modifier("l", "L");
        break;
     case 0x27:
        print_modifier("oe", "OE");
        break;
     case 0x28:
        print_modifier("ae", "AE");
        break;
     case 0x29:
        print_modifier("#", "'");
        break;
     case 0x2A:
        shift = true;
        break;
     case 0x2B:
        print_modifier("#", "'");
        break;
     case 0x2C:
        print_modifier("y", "Y");
        kprintf("y");
        break;
     case 0x2D:
        print_modifier("x", "X");
        break;
     case 0x2E:
        print_modifier("c", "C");
        kprintf("c");
        break;
     case 0x2F:
        print_modifier("v", "V");
        break;
     case 0x30:
        print_modifier("b", "B");
        break;
     case 0x31:
        print_modifier("n", "N");
        break;
     case 0x32:
        print_modifier("m", "M");
        break;
     case 0x33:
        print_modifier(",", ";");
        break;
     case 0x34:
        print_modifier(".", ":");
        break;
     case 0x35:
        print_modifier("-", "_");
        break;
     case 0x36:
        shift = true;
        break;
     case 0x37:
        kprintf("KEYPAD");
        break;
     case 0x38:
        kprintf("LEFT ALT");
        break;
     case 0x39:
        kprintf(" ");
        break;
     case 0x3A:
        caps = true;
        break;
     case 0x3B:
        kprintf("F1");
        break;
     case 0x3C:
        kprintf("F2");
        break;
     case 0x3D:
        kprintf("F3");
        break;
     case 0xB6:
        shift = false;
        break;
     case 0xAA:
        shift = false;
        break;
     case 0xBA:
        caps = false;
        break;
    default:
        //kprintf("ERROR");
        break;
  }
}
