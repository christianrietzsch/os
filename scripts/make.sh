#/bin/bash

gcc -m32 -ffreestanding -c -o boot/objects/start.o boot/start.S
gcc -m32 -ffreestanding -Wall -g -fno-stack-protector -nostdinc -c -o boot/objects/init.o init.c
ld -melf_i386 -Tboot/kernel.ld -o kernel boot/objects/init.o boot/objects/start.o
