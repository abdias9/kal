CFLAGS=-std=gnu99 -ffreestanding -O2 -nostdlib -lgcc -Wall -Wextra
OBJ=boot.o kernel.o vga.o string.o sys.o keys.o math.o memory.o cdrom.o
EXEC=../bin/kal.bin
CC=/opt/cross/bin/i686-elf-gcc
ASM=/opt/cross/bin/i686-elf-as
#ASM=nasm

all: kal

kal: $(OBJ)
	$(CC) -T linker.ld -o $(EXEC) $(CFLAGS) $(OBJ)

boot.o: boot.s
	$(ASM) boot.s -o boot.o

#boot.o: boot.asm
#	$(ASM) -felf32 boot.asm -o boot.o

kernel.o: kernel.c
	$(CC) -c kernel.c -o kernel.o $(CFLAGS)

vga.o: vga.c
	$(CC) -c vga.c -o vga.o $(CFLAGS)

string.o: string.c
	$(CC) -c string.c -o string.o $(CFLAGS)

sys.o: sys.c
	$(CC) -c sys.c -o sys.o $(CFLAGS)

keys.o: keys.c
	$(CC) -c keys.c -o keys.o $(CFLAGS)

math.o: math.c
	$(CC) -c math.c -o math.o $(CFLAGS)

memory.o: memory.c
	$(CC) -c memory.c -o memory.o $(CFLAGS)

cdrom.o: cdrom.c
	$(CC) -c cdrom.c -o cdrom.o $(CFLAGS)

#shell.o: shell.c
#	$(CC) -c shell.c -o shell.o $(CFLAGS)

clean: 
	rm -rf *.o

mrproper: clean
	rm -rf ../bin/kal.bin
