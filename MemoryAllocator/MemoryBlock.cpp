#include "MemoryBlock.h"
#include <cstdlib>
#include <stdexcept>

MemoryBlock::MemoryBlock(size_t size)
{
	allocated = false;
	next = nullptr;
	blockSize = size;
	blockPool = (unsigned char*)malloc(size);
	if (!blockPool) {
		throw std::runtime_error("Allocation failed");
	}
}
MemoryBlock::~MemoryBlock() {
	free(blockPool);
}
