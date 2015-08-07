#include "sys.h"

unsigned char inportb(unsigned short port) {
	unsigned char result;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (result) : "dN" (port));
	return result;
}

void outportb(unsigned short port, unsigned char data) {
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}
