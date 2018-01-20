#include "Allocator.hpp"


Magma::StandardAllocator::~StandardAllocator()
{
	if (m_allocated.size() != 0) std::wcerr << L"Warning: standard allocator destroyed while there were still objects allocated in it" << std::endl;
}

void * Magma::StandardAllocator::Allocate(size_t size)
{
	auto alloc = malloc(size);
	m_allocated.push_back(std::make_pair(size, alloc));
	return alloc;
}

void Magma::StandardAllocator::Deallocate(void * ptr)
{
	m_allocated.remove_if([ptr](std::pair<size_t, void*> p) -> bool { return p.second == ptr; });
	free(ptr);
}

size_t Magma::StandardAllocator::GetSize()
{
	return this->GetAllocatedSize();
}

size_t Magma::StandardAllocator::GetAllocatedSize()
{
	size_t size = 0;
	for (auto& p : m_allocated)
		size += p.first;
	return size;
}
