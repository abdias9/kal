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
		vga_terminal_putint(memory_free_block_size((FreeBlock*)ptr));
		ptr++;
	}
}

uint64_t memory_free_block_size(FreeBlock* block) {
	return block->end - block->start;
}

void* memory_alloc(size_t sz) {
    FreeBlock* block = (FreeBlock*) MEMORY_FREE_AREA_START;
    while (*((uint64_t*)block) != 0) {
        if (memory_free_block_size(block) > sz + 1) {
            uint8_t* address = (uint8_t*)block->start;
            block->start += sz + 1; 
			*address = sz;
            return ++address;
        }
		block++;
    }
	return NULL;
}

void memory_free(void* address) {
	uint8_t *p_start = (uint8_t*) address;
	uint8_t *p_end = p_start;
	uint8_t len = *(--p_start);
	p_end += len;
	FreeBlock* block = (FreeBlock*) MEMORY_FREE_AREA_START;
	while (*((uint64_t*) block) != 0) {
		if (block->start == p_end) {
			FreeBlock* block2 = block;
			while (*((uint64_t*)(++block2)) != 0) 
				if (block2->end == p_start) {
					block2->end = block->end;
					memory_free_block_delete(block);
					return;
				}
			block->start -= len + 1;
			return;	
		}
		if (block->end == p_start) {
			FreeBlock* block2 = block;
			while (*((uint64_t*)(++block2)) != 0) 
				if (block2->start == p_end) {
					block->end = block2->end;
					memory_free_block_delete(block2);
					return;
				}
			block->end += len + 1;
			return;
		}
		block++;
	}	
	memory_free_block_alloc(p_start, p_end);		
}

void memory_print_status() {
	size_t free_bytes = 0, total = MEMORY_EXTENDED_END - MEMORY_EXTENDED_START;
	FreeBlock* block = (FreeBlock*) MEMORY_FREE_AREA_START;
	while (*((uint64_t*) block) != 0) {
		free_bytes += memory_free_block_size(block);
		block++;
	}
	printf("Used: %d bytes\nFree: %d bytes\nTotal: %d bytes\n", total - free_bytes, free_bytes, total);	
}
