#include "Allocator.h"
#include <stdexcept>

Allocator::Allocator(size_t total_size)
{
	MemoryBlock head = MemoryBlock(total_size);
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
	curr->next = &MemoryBlock(size);
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
			free(curr->blockPool);
		}
	}
	head.allocated = head.allocated + deallocatedSize;
	return;
}