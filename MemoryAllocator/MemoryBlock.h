#pragma once
class MemoryBlock
{
public:
	MemoryBlock(size_t size=0U, size_t offset=0U);
	bool allocated;
	MemoryBlock* next;
	size_t blockOffset;
	size_t blockSize;
};

