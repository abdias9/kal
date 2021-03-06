#ifndef __i386__
#error "Invalid Architecture!"
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
	
	char* a = ftoa(25.25, 2);
	//free(s);
	//printf("%f", 2.25);

	//memory_free_print_blocks(10);
	memory_print_status();
	
}
