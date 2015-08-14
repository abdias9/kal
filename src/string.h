#ifndef MSTRING_INCLUDED
#define MSTRING_INCLUDED

#include <stddef.h>
#include <stdint.h>

uint8_t* memcpy(uint8_t *dest, const uint8_t *src, size_t count);
uint8_t* memset(uint8_t *dest, uint8_t value, size_t count);
uint16_t* memsetw(uint16_t *dest, uint16_t value, size_t count);
size_t memcmp(const uint8_t *ptr1, const uint8_t *ptr2, size_t count);

char* strtok(char* str, char c);
size_t strlen(const char* str);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t count);
char* strcat(char* dest, const char* src);
char* strncat(char* dest, const char* src, size_t count);
int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t count);
size_t str_char_count(const char* str, char c);

void swap(char *c1, char *c2);
void reverse(char str[], int len);

#define BASE_DECIMAL 10
#define BASE_BINARY 2
#define BASE_HEXADECIMAL 8

int atoi(char* a);
char* itoa(int num, int base);
char* ftoa(double n, int afterpoint);

#endif
