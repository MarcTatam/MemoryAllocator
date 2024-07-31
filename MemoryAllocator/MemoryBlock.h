#pragma once
class MemoryBlock
{
public:
	MemoryBlock(size_t size=0);
	bool allocated;
	MemoryBlock* next;
	unsigned char* blockPool;
	size_t blockSize;
};

