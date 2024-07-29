#include "Allocator.h"
#include <cstdlib>
#include <stdexcept>

Allocator::Allocator(size_t total_size)
{
	memory = malloc(total_size);
	if (!memory) {
		throw std::runtime_error("Inital allocation failed");
	}
	return;
}

void* Allocator::allocate(size_t size)
{
	return;
}

void Allocator::deallocate(void* ptr)
{
	return;
}