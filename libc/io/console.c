#include "../math/math.h"
#include "../string/string.h"
#include "serial.h"

typedef __builtin_va_list va_list;
#define va_start(ap, X)   __builtin_va_start(ap, X)
#define va_arg(ap, type)  __builtin_va_arg(ap, type)
#define va_end(ap)        __builtin_va_end(ap) 

#define LINE_LENGTH 160
#define LINE_ROWS 80
#define COLOR 0x07
#define TAB_LENGTH 8

char* video = (char*)0xb8000;
int current = 0;
//no need for &current in print functions when its a "global" variable
//implement hex function for pointers

void update_cursor()
{
  outb(0x3D4, 14);
  outb(0x3D5, current/2 >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, current/2);  
}

void print_char(char chr)
{
  //more \ formatting options 
  if(chr == '\n') 
  {
    int line_rest = LINE_LENGTH-(current%LINE_LENGTH);
    current += line_rest;
    return;
  }
  if(chr == '\t') 
  {
    current += TAB_LENGTH;
    return;
  }
  video[current] = chr;
  video[current+1] = COLOR;
  current += 2;
  update_cursor();
}

void print_string(char* string)
{
  for(int i = 0; string[i] != '\0'; i++)
  {
    print_char(string[i]);
  }
}

void clear()
{
  for(int i = current; i < LINE_LENGTH*LINE_ROWS; i++) 
  {
    print_char(' ');
  }
  current = 0;
  update_cursor();
}

void print_int(int number)
{
  int max_length = count_digits(number);
  int digits = 0;
  // 0123 ; first digit zero does not work
  int numbers[max_length];
  for(int i = 0; i < max_length; i++) {
    int n = number%pow(10,i+1)-digits;
    digits += n;
    int length = count_digits(n);
    int div = pow(10, length-1);
    n /= div == 0 ? 1 : div;
    if(n < 0 && div != pow(10, max_length-1)) {n = -1*n;}
    //reverse loop instead of using an array
    numbers[max_length-i-1] = n;
  }
  for(int j = 0; j < max_length; j++) 
  {
    print_char((char)(numbers[j]+48));
  }
}
void kprintf(char* str, ...)
{
  //add formats like .2; check if %d is actually an integer
  if(search_char(str, '%', 0) == -1)
  {
    print_string(str);
    return;
  }
  va_list args;
  va_start(args, str);
  int pos = search_char(str, '%', 0);
  int last = 0;
  while(pos != -1)
  {
    for(int i = last; i < pos; i++) 
    {
      print_char(str[i]);
    }
    char specifier = str[pos+1];
    if(specifier == 's') {print_string(va_arg(args, char*));}    
    if(specifier == 'c') {print_char(va_arg(args, int));}
    if(specifier == 'd') {print_int(va_arg(args, int));}
    last = pos+2;
    pos = search_char(str, '%', pos+1);
  }
  va_end(args);
  update_cursor();
}
// get up to % symbol; check for datatype: print datatype

