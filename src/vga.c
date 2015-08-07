#include <stdbool.h>
#include "vga.h"
#include "string.h"
#include "sys.h"
#include "keys.h"

uint8_t vga_build_color(uint8_t fg, uint8_t bg) {
	return fg | bg << 4;
}

uint16_t vga_build_char(char c, uint8_t color) {
	uint16_t c16 = c;
	return c16 | (uint16_t)color << 8;
}

void vga_terminal_clear() {
	memsetw((uint16_t*) VGA_ADDRESS, vga_build_char(' ', vga_build_color(COLOR_WHITE, COLOR_BLACK)), VGA_W * VGA_H); 
	terminal_row = terminal_column = 0;
	vga_terminal_update_caret();
}

void vga_terminal_initialize(uint8_t color) {
	terminal_row = terminal_column = 0;
	terminal_color = color;
	terminal_buffer = (uint16_t*) VGA_ADDRESS;
	for (size_t y = 0; y < VGA_H; y++)
		for (size_t x = 0; x < VGA_W; x++) {
			const size_t index = y * VGA_W + x;
			terminal_buffer[index] = vga_build_char(' ', terminal_color);
		}
}

void vga_terminal_putchar_at(char c, uint8_t color, size_t x, size_t y) {
	terminal_buffer[y * VGA_W + x] = vga_build_char(c, color);	
	vga_terminal_update_caret();
}

void vga_terminal_putchar(char c) {
	switch (c) {
		case '\n':
			terminal_row++;
			terminal_column = 0;
			break;
		case '\r':
			terminal_column = 0;
			break;
		case '\b':
			if (terminal_column != 0) 
				vga_terminal_putchar_at(' ', terminal_color, --terminal_column, terminal_row);
			break;
		default:
			if (terminal_column != VGA_W)
				vga_terminal_putchar_at(c, terminal_color, terminal_column++, terminal_row);
			else if (terminal_row == VGA_H) {
				terminal_column = 0;
				terminal_row = 0;
				vga_terminal_putchar_at(c, terminal_color, terminal_column++, terminal_row);
			} else {
				terminal_column = 0;
				terminal_row++;
				vga_terminal_putchar_at(c, terminal_color, terminal_column++, terminal_row);
			}
			break;
	}
	vga_terminal_update_caret();
}

void vga_terminal_puts(const char* str) {
	while (*str != 0) 
		vga_terminal_putchar(*str++);
}

void vga_terminal_puts_colored(const char* str, uint8_t color) {
	uint8_t last_color = terminal_color;
	vga_terminal_set_color(color);
	while (*str != 0)
		vga_terminal_putchar(*str++);
	vga_terminal_set_color(last_color);
}

void vga_terminal_set_color(uint8_t color) {
	terminal_color = color;
}

void vga_terminal_update_caret() {
	size_t caret = terminal_row * VGA_W + terminal_column;
	outportb(0x3D4, 14);
    outportb(0x3D5, caret >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, caret);
}

char vga_terminal_getchar() {
	unsigned char scan = 0;
	while (keys[scan] == 0)
		scan = inportb(KEYBOARD_ADDRESS_INPUT);
	return keys[scan];
}

char* vga_terminal_getstring() {
	static char str[128] = "";
	size_t len = 0;
	unsigned char scan = 0, last_scan = 0;
	do {
		scan = inportb(KEYBOARD_ADDRESS_INPUT);
		if (keys[scan] != 0 && scan != last_scan && keys[scan] != '\n') {
			vga_terminal_putchar(keys[scan]);
			str[len++] = keys[scan];
		}
		last_scan = scan;
	} while (keys[scan] != '\n');
	str[strlen(str)] = '\0';
	return str;
}

int vga_terminal_printf(const char* format, ...) {
	size_t len = strlen(format);
	va_list vl;
	va_start(vl, format);

	for (size_t i = 0; i < len; i++) {
		if (format[i] == '%') {
			switch (format[i + 1]) {
				case 'c':
					vga_terminal_putchar(va_arg(vl, int));
					break;
				case 's':
					vga_terminal_puts(va_arg(vl, char*));
					break;
				case 'd':
					vga_terminal_puts(itoa(va_arg(vl, int), BASE_DECIMAL));
					break;
				case 'f':
					vga_terminal_puts(ftoa(va_arg(vl, double), 4));
					break;
				case 'b':
					if (va_arg(vl, int))
						vga_terminal_puts("True");
					else
						vga_terminal_puts("False");
					break;
				case '%':
					vga_terminal_putchar('%');
					break;
				default:
					vga_terminal_puts("Could not find!");
					break;
			}
			i += 1;
		} else
			vga_terminal_putchar(format[i]);	
	}

	va_end(vl);

	return 0;
}	
