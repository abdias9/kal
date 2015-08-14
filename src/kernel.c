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
	vga_terminal_puts("\n.::   .::        .:       .::      \n.::  .::        .: ::     .::      \n.:: .::        .:  .::    .::      \n.: .:         .::   .::   .::      \n.::  .::     .:::::: .::  .::      \n.::   .::   .::       .:: .::      \n.::     .::.::         .::.::::::::\n");
	vga_terminal_puts("\n          K. A. L. v0.0.1a");
	vga_terminal_puts("\n-------------------------------------\n");

	memory_initialize();
	vga_terminal_puts_colored("[kernel] ", THEME_RED);
	vga_terminal_puts("Memory management initialized!\n");
	
	char* str = (char*) malloc(sizeof(char) * 10);
	strcpy(str, "000000000");
	char* str1 = (char*) malloc(sizeof(char) * 5);
	strcpy(str1, "1111");
	
	memory_free(str);

	memory_free_print_blocks(10);
	
}
