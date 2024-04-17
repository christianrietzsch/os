#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "keyboard.c"

void init_keyboard();
void keyboard_handler(uint8_t);
void send_command(uint8_t);

#endif
