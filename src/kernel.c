#if defined(__linux__)
#error "NOT INTO LINUX!"
#endif

#if !defined(__i386__)
#error "Invalid Compiler!"
#endif

#include "vga.h"
#include "sys.h"
#include "keys.h"
#include "memory.h"
#include "string.h"

void kernel_main() {
	vga_terminal_initialize(vga_build_color(COLOR_WHITE, COLOR_BLACK));
	//vga_terminal_puts(" >: ");
	//vga_terminal_set_color(vga_build_color(COLOR_GREEN, COLOR_BLACK));
	vga_terminal_puts("\n.::   .::        .:       .::      \n.::  .::        .: ::     .::      \n.:: .::        .:  .::    .::      \n.: .:         .::   .::   .::      \n.::  .::     .:::::: .::  .::      \n.::   .::   .::       .:: .::      \n.::     .::.::         .::.::::::::\n");
	vga_terminal_puts("\n          K. A. L. v0.0.1a");
	vga_terminal_puts("\n-------------------------------------\n");

	memory_initialize();
	vga_terminal_puts_colored("[kernel] ", THEME_RED);
	vga_terminal_puts("Memory management initialized!\n");

	vga_terminal_printf("%d", sizeof(BitMap));

	char* str = (char*) memory_alloc(sizeof(char) * 10);
	strcpy(str, "emanuel");
	memory_free(str);
	char* str1 = (char*) memory_alloc(sizeof(char) * 5);
	strcpy(str1, "tes");

	vga_terminal_puts(str1);
	
}
