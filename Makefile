kernel.bin: kernel.elf
	objcopy -O binary kernel.elf kernel.bin

kernel.elf: linker.ld boot.o kernel.o
	ld -nostdlib -Tlinker.ld boot.o kernel.o -o kernel.elf

kernel.o: kernel.c stchee.h
	gcc -ffreestanding -g -c kernel.c -o kernel.o

boot.o: boot.s
	as -o boot.o boot.s
