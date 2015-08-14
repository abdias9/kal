#include "string.h"
#include "memory.h"
#include "math.h"
#include "vga.h"

size_t str_char_count(const char* str, char c) {
	size_t res = 0;
	while (*str != 0) 
		if (*str++ == c)
			res++;
	return res;
}

char* strtok(char* str, char c) {
	size_t i = 0;
	while (str[i] != 0) {
		if (str[i] == c) {
			char* res = (char*) memory_alloc(sizeof(char) * (i + 1));
			char* temp = (char*) memory_alloc((sizeof(char) * strlen(str) - i + 1));
			strncpy(res, str, i);
			strcpy(str, str + i + 1);
			memory_free(temp);
			return res;
		}	
		i++;
	}
	return str;
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len] != 0) 
		len++;
	return len;
}

char* strcpy(char* dest, const char* src) {
	char* pdest = dest;
	const char* psrc = src;
	while (*psrc != 0)
		*pdest++ = *psrc++;
	*pdest = '\0';
	return dest; 	
}

char* strncpy(char* dest, const char* src, size_t count) {
	char* pdest = dest;
	const char* psrc = src;
	for (; count != 0; count--)
		*pdest++ = *psrc++;
	*pdest = '\0';
	return dest;
}

int strcmp(const char* str1, const char* str2) {
	for (; *str1 == *str2; str1++, str2++)
		if (*str1 == 0)
			return 0;
	return ((*(unsigned char*) str1 < *(unsigned char*) str2) ? -1 : 1);
}

int strncmp(const char* str1, const char* str2, size_t count) {
	while (count--)
		if (*str1++ != *str2++)
			return *(unsigned char*)(str1 - 1) - *(unsigned char*)(str2 - 1);
	return 0;
}

char* strcat(char* dest, const char* src) {
	size_t start = strlen(dest), i = 0;
	while (*src != 0)
		dest[start + i++] = *src++;
	return dest;
}

char* strncat(char* dest, const char* src, size_t count) {
	size_t start = strlen(dest), i = 0;
	for (; count != 0; count--)
		dest[start + i++] = *src++;
	return dest;
}

uint8_t *memcpy(uint8_t *dest, const uint8_t *src, size_t count) {
	uint8_t *pdest = dest;
	const uint8_t *psrc = src;
	for (;count != 0; count--)
		*pdest++ = *psrc++;
	return dest;
		
}

uint8_t *memset(uint8_t *dest, uint8_t value, size_t count) {
	uint8_t *pdest = dest;
	for (;count != 0; count--)
		*pdest++ = value;
	return dest;
}

uint16_t *memsetw(uint16_t *dest, uint16_t value, size_t count) {
	uint16_t *pdest = dest;
	for (;count != 0; count--)
		*pdest++ = value;
	return dest;
}

size_t memcmp(const uint8_t *ptr1, const uint8_t *ptr2, size_t count) {
	for (; count != 0; count--) {
		short int diff = *ptr1++ - *ptr2++;
		if (diff != 0) return diff;			
	}			
	return 0;
}

void swap(char *c1, char *c2) {
	char temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

void reverse(char str[], int len) {
	int start = 0, end = len - 1;
	while (start < end) {
		swap(str + start, str + end);
		start++;
		end--;
	}
}

int atoi(char *a) {
	int res = 0, sign = 1, i = 0;
	
	if (a[0] == '-') {
		sign = -1;
		i++;
	}

	for (; a[i] != '\0'; ++i)
		res = res * 10 + a[i] - '0';
	return sign * res;
}

char* itoa(int num, int base) {
	int i = 0;
	bool is_negative = false;
	char* str = (char*) memory_alloc(sizeof(char) * 20);

	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}	

	if (num < 0 && base == 10) {
		is_negative = true;
		num = -num;
	}

	while (num != 0) {
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	if (is_negative)
		str[i++] = '-';

	str[i] = '\0';
	reverse(str, i);
	return str;
}

char* ftoa(double n, int afterpoint) {
	int left_side_i = (int) n;
	char *left_side = itoa(left_side_i, BASE_DECIMAL);
	char *right_side = (char*) memory_alloc(sizeof(char) * (afterpoint + 1));
	strcpy(right_side, ".");
	n -= (double) left_side_i;
	do {
		n = n * (double)10;
		int n_i = (int) n;
		n -= (double) n_i;
		strcat(right_side, itoa(n_i, BASE_DECIMAL));
	} while (--afterpoint != 0);
	char* res = (char*)memory_alloc(sizeof(char) * (strlen(left_side) + afterpoint + 1));
	strcpy(res, left_side);
	strcat(res, right_side);
	return res;
}
