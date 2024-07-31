#pragma once
#include "MemoryBlock.h"

class Allocator
{
public:
	Allocator(size_t total_size);
	void* allocate(size_t size);
	void deallocate(void* ptr);

private:
	MemoryBlock head;
	size_t free;
	size_t allocated;
	unsigned char* pool;
};

