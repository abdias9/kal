#ifndef MEMORY2_INCLUDED
#define MEMORY2_INCLUDED

//#define MEMORY_EXTENDED_START 0x01000000
#define MEMORY_EXTENDED_START 0x010F0000
#define MEMORY_EXTENDED_END   0x010F03E8

#define MEMORY_FREE_AREA_START 0x02000000

#define memory_alloc malloc
#define memory_free free

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "vga.h"

#define CONTACT_LEFT 0
#define CONTACT_RIGHT 1

typedef struct {
	uint8_t* start; 
	uint8_t* end;
} FreeBlock;

void memory_initialize();
void memory_free_block_delete(FreeBlock* block);
void memory_free_block_alloc(void* start, void* end);
void memory_free_print_blocks(size_t count);
uint64_t memory_free_block_size(FreeBlock* block);
bool memory_free_have_contact(void* address, uint8_t type);

void* memory_alloc(size_t sz);
void memory_free(void* address);

#endif
