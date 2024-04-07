#/bin/bash

gcc -m32 -ffreestanding -c -o objects/start.o boot/start.S
gcc -m32 -ffreestanding -Wall -g -fno-stack-protector -nostdinc -c -o objects/init.o init.c
ld -melf_i386 -Tboot/kernel.ld -o kernel objects/init.o objects/start.o
