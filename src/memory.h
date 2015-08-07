#ifndef MEMORY_INCLUDED
#define MEMORY_INCLUDED

#define MEMORY_START 0x00007E00
#define MEMORY_END 0x00008000
#define MEMORY_BLOCKS 51200

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
	void* address;
	bool is_free, is_flag;
} BitMap;

void* mem;
BitMap bmem[MEMORY_BLOCKS];

void memory_initialize();
void memory_print();
void* memory_alloc(size_t sz);
void memory_free(void* address);
bool memory_find_block_seg(size_t start, size_t sz);

#endif
