#include "memory.h"
#include "math.h"
#include "vga.h"

void memory_initialize() {
	mem = (void*) MEMORY_START;
	uint8_t* block = (uint8_t*) mem;
	for (size_t bcount = 0; bcount != MEMORY_BLOCKS; bcount++) {
		bmem[bcount].address = (void*)block++;
		bmem[bcount].is_free = true;
		bmem[bcount].is_flag = false;
	}
}

void* memory_alloc(size_t sz) {
	for (size_t g = 0; g != MEMORY_BLOCKS; g++) {
		if (bmem[g].is_free) 
			for (size_t i = 0; i != sz + 1; i++)
				if (!bmem[g + i].is_free) {
					g = g + i + 1;
					break;
				} else if (g + i + 1 == g + sz) {
					for (size_t b = 0; b != sz; b++) {
						bmem[g + b].is_free = false;
						bmem[g + b].is_flag = false;
					}
					bmem[g + sz].is_free = false;
					bmem[g + sz].is_flag = true;
					return bmem[g].address;
				}
	}
	return NULL;
}

void memory_free(void* address) {
	for (size_t i = 0; i != MEMORY_BLOCKS; i++)
		if (bmem[i].address == address) {
			for (size_t j = i; j != MEMORY_BLOCKS; j++) {
				if (bmem[j].is_flag == true) {
					bmem[j].is_free = true;
					bmem[j].is_flag = false;
					return;
				}
				bmem[j].is_free = true;
				bmem[j].is_flag = false;						
			}
		}
}

void memory_print() {
	for (size_t i = 0; i != MEMORY_BLOCKS; i++)
		if (bmem[i].is_flag)
			vga_terminal_putchar('F');
		else if (bmem[i].is_free)
			vga_terminal_putchar('0');
		else
			vga_terminal_putchar('X');
							
}

void memory_print_stats() {
	size_t free = 0;
	for (size_t i = 0; i != MEMORY_BLOCKS; i++)
		if (bmem[i].is_free)
			free++;
	vga_terminal_puts("--- Memory Status ---\n");
	vga_terminal_puts_colored("FREE: ", THEME_GREEN);
	vga_terminal_printf("%d bytes\n", free);
	vga_terminal_puts_colored("USED: ", THEME_GREEN);
	vga_terminal_printf("%d bytes\n", MEMORY_BLOCKS - free);
	vga_terminal_puts_colored("TOTAL: ", THEME_GREEN);
	vga_terminal_printf("%d bytes\n", MEMORY_BLOCKS);
}
