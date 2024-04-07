#ifndef IO_H
#define IO_H

#include "console.c"
void print_string(char* string_to_print);
void print_char(char char_to_print);
void print_int(int int_to_print);
void clear();
void kprintf(char* string_to_format_and_print, ...);

#endif
