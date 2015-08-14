#include "memory.h"
#include "string.h"

void memory_initialize() {
	memory_free_block_alloc((void*)MEMORY_EXTENDED_START, (void*)MEMORY_EXTENDED_END);	
}

void memory_free_block_delete(FreeBlock* block) {
	uint64_t *ptr = (uint64_t*) block;
	uint64_t *eptr = (uint64_t*) block;
	if (ptr[1] == 0) {
		*ptr = 0;
		return;
	}

	while (*(++eptr) != 0);
	*ptr = *(--eptr);
	*eptr = 0;
}

void memory_free_block_alloc(void* start, void* end) {
	uint64_t *ptr = (uint64_t*)MEMORY_FREE_AREA_START;
	while (*ptr != 0) 
		ptr++;
	FreeBlock* block = (FreeBlock*)ptr;
	block->start = start;
	block->end = end;
}

void memory_free_print_blocks(size_t count) {
	uint64_t *ptr = (uint64_t*)MEMORY_FREE_AREA_START;
	for (; count != 0; count--) { 
		if (*ptr == 0)
			break;
		vga_terminal_puts(itoa(memory_free_block_size((FreeBlock*)ptr), 10));
		vga_terminal_putchar('\n');
		ptr++;
	}
}

uint64_t memory_free_block_size(FreeBlock* block) {
	return block->end - block->start;
}

void* memory_alloc(size_t sz) {
    FreeBlock* block = (FreeBlock*) MEMORY_FREE_AREA_START;
    while (*((uint64_t*)block) != 0) {
        if (memory_free_block_size(block) > sz + 1) {//+1
            uint8_t* address = (uint8_t*)block->start;
            block->start += sz + 1; //+1
			*address = sz;
            return ++address;
        }
		block++;
    }
	return NULL;
}

void memory_free(void* address) {
	uint8_t *p_start = (uint8_t*) address;
	p_start--;
	size_t len = *p_start;
	uint8_t *p_end = (uint8_t*)address;
	p_end = p_end + len;
	FreeBlock* block = (FreeBlock*) MEMORY_FREE_AREA_START;
	while (*((uint64_t*) block) != 0) {
		if (block->start == p_end) {
			block->start -= len + 1;
			return;	
		}
		if (block->end + 1 == p_start) {
			block->end += len + 1;
			return;
		}
		block++;
	}	
	memory_free_block_alloc(p_start, p_end);		
}

bool memory_free_have_contact(void* address, uint8_t type) {
	
}
