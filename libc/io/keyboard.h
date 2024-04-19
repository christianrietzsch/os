#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "keyboard.c"

void init_keyboard();
void print_letter(unsigned char);
void send_command(uint8_t);

#endif
