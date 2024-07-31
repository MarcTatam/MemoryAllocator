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
}

void Allocator::deallocate(void* ptr)
{
	return;
}