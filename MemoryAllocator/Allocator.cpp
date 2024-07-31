#include "Allocator.h"
#include <stdexcept>

Allocator::Allocator(size_t total_size) : head(total_size)
{
	
}

void* Allocator::allocate(size_t size)
{
	if (head.allocated < size) {
		throw std::runtime_error("Out of memory");
	}
	head.allocated = head.allocated - size;
	MemoryBlock* curr = &head;
	while (!(curr->next == nullptr)) {
		curr = curr->next;
	}
	MemoryBlock* newBlock = new MemoryBlock(size);
	curr->next = newBlock;
	curr = curr->next;
	return (void*)curr->blockPool;
}

void Allocator::deallocate(void* ptr)
{
	MemoryBlock* curr = head.next;
	MemoryBlock* prev = &head;
	size_t deallocatedSize = 0U;
	while (!(curr->next == nullptr)) {
		if ((void*)curr->blockPool == ptr) {
			prev->next = curr->next;
			deallocatedSize = curr->blockSize;
			delete curr;
			break;
		}
		curr = curr->next;
	}
	head.allocated = head.allocated + deallocatedSize;
	return;
}