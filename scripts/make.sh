#/bin/bash

gcc -m32 -ffreestanding -c -o boot/start.o boot/start.S
gcc -m32 -ffreestanding -Wall -g -fno-stack-protector -nostdinc -c -o boot/init.o init.c
ld -melf_i386 -Tboot/kernel.ld -o kernel boot/init.o boot/start.o
