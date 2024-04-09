#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "keyboard.c"

void init_keyboard();
void irq_handler(uint8_t);

#endif
