#include "MemoryBlock.h"

MemoryBlock::MemoryBlock(size_t size, size_t offset)
{
	allocated = false;
	next = nullptr;
	blockSize = size;
	blockOffset = offset;
}