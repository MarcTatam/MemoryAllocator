#pragma once
class MemoryBlock
{
public:
	bool allocated;
	MemoryBlock* next;
	unsigned char* block_pool;
	size_t block_size;

	MemoryBlock(size_t size);
};

