#ifndef VGA_INCLUDED
#define VGA_INCLUDED

#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_BROWN 6
#define COLOR_LIGHT_GREY 7
#define COLOR_DARK_GREY 8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED 12
#define COLOR_LIGHT_MAGENTA 13
#define COLOR_LIGHT_BROWN 14
#define COLOR_WHITE 15

#define THEME_RED (COLOR_RED | COLOR_BLACK << 4)
#define THEME_STD (COLOR_WHITE | COLOR_BLACK << 4)
#define THEME_GREEN (COLOR_GREEN | COLOR_BLACK << 4)
#define THEME_TITLE (COLOR_WHITE | COLOR_DARK_GREY << 4)

#define vga_terminal_printf printf
#define vga_terminal_puts puts

#define VGA_W 80
#define VGA_H 25
#define VGA_ADDRESS 0xB8000

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

size_t terminal_row, terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

uint8_t vga_build_color(uint8_t fg, uint8_t bg);
uint16_t vga_build_char(char c, uint8_t color);
void vga_terminal_clear();
void vga_terminal_update_caret();
void vga_terminal_initialize(uint8_t color);
void vga_terminal_putchar_at(char c, uint8_t color, size_t x, size_t y);
void vga_terminal_putchar(char c);
void vga_terminal_set_color(uint8_t color);
void vga_terminal_puts(const char* str);
void vga_terminal_puts_colored(const char* str, uint8_t color);
void vga_terminal_putint(int i);
void vga_terminal_putfloat(double f);
char vga_terminal_getchar();
char* vga_terminal_getstring();

int vga_terminal_printf(const char* format, ...);

#endif
