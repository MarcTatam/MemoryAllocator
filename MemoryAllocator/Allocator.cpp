#include "Allocator.h"
#include <cstdlib>
#include <stdexcept>

Allocator::Allocator(size_t total_size=0) : head(total_size)
{
	allocated = 0U;
	free = total_size;
	pool = (unsigned char*) malloc(total_size);
	if (!pool) {
		throw std::runtime_error("Failed to allocate memory");
	}
}

void* Allocator::allocate(size_t size)
{
	if (free < size) {
		throw std::runtime_error("Out of memory");
	}
	MemoryBlock* curr = &head;
	while (!(curr->next == nullptr)) {
		if (!curr->allocated && curr->blockSize >= size) {
			break;
		}
		curr = curr->next;
	}
	if (curr->allocated && curr->blockSize < size) {
		//If this block is allocated we have reached the end of the list, so need to create new block
		throw std::runtime_error("No suitably sized Memory Blocks are available!");
	}
	if (curr->allocated) {
		//If this block is allocated we have reached the end of the list, so need to create new block
		MemoryBlock* newBlock = new MemoryBlock(size, curr->blockOffset+curr->blockSize);
		curr->next = newBlock;
		curr = curr->next;
	}
	if (curr->blockSize>size) {
		//Split block if oversized
		size_t excess = curr->blockSize - size;
		MemoryBlock* newBlock = new MemoryBlock(excess, curr->blockOffset+excess);
		newBlock->next = curr->next;
		curr->blockSize = size;
		curr->next = newBlock;
	}
	curr->allocated = true;
	unsigned char* usable_memory = pool + curr->blockOffset;
	free -= size;
	allocated += size;
	return (void*) usable_memory;
}

void Allocator::deallocate(void* ptr)
{
	MemoryBlock* curr = head.next;
	MemoryBlock* prev = &head;
	while (!(curr == nullptr)) {
		void* this_pool = pool + curr->blockOffset;
		if (this_pool == ptr) {
			break;
		}
		curr = curr->next;
	}
	if (curr == nullptr) {
		throw std::runtime_error("Memory could not be found!");
	}
	curr->allocated = false;
	if (!curr->next) {
		return;
	}
	MemoryBlock* nextBlock = curr->next;
	while (!nextBlock->allocated) {
		// Merge sequential blocks if they are unallocated
		curr->blockSize += nextBlock->blockSize;
		curr->next = nextBlock->next;
		delete nextBlock;
		nextBlock = curr->next;
	}
	return;
}