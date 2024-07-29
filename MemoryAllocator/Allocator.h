#pragma once
class Allocator
{
	public:
		Allocator(size_t total_size);
		void* allocate(size_t size);
		void deallocate(void* ptr);
};

