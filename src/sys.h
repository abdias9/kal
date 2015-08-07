#ifndef SYS_H_INCLUDED
#define SYS_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

unsigned char inportb(unsigned short port);
void outportb(unsigned short port, unsigned char data);

#endif
