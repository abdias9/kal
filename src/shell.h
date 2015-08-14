#ifndef SHELL_INCLUDED
#define SHELL_INCLUDED

#include "string.h"
#include "memory.h"
#include "vga.h"

typedef struct {
	char* name;
	char* description;
	void* function;
} CommandTable;

typedef struct {
	char *name;
	char **params;
} Command;

void shell_loop();
Command shell_get_command();
void shell_exec_command(Command cmd);

void shell_echo(char *str);

#endif
