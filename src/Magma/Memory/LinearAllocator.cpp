#include "LinearAllocator.hpp"

Magma::LinearAllocator::LinearAllocator(size_t size)
{
	m_size = size;
	m_allocatedSize = 0;
	m_start = (char*)malloc(m_size);
	m_end = m_start + m_size;
	m_head = m_start;

	std::wcout << L"Constructed linear allocator with size " << m_size << std::endl;
}

Magma::LinearAllocator::~LinearAllocator()
{
	std::wcout << L"Deconstructed linear allocator with size " << m_size << std::endl;

	free(m_start);
	m_start = nullptr;
	m_end = nullptr;
	m_head = nullptr;
}

void Magma::LinearAllocator::Clear()
{
	m_head = m_start;
}

void * Magma::LinearAllocator::Allocate(size_t size)
{
	if (m_head + size >= m_end)
		return nullptr;
	auto alloc = m_head;
	m_head += size;
	m_allocatedSize += size;
	return alloc;
}

void Magma::LinearAllocator::Deallocate(void * ptr)
{
	
}

size_t Magma::LinearAllocator::GetSize()
{
	return m_size;
}

size_t Magma::LinearAllocator::GetAllocatedSize()
{
	return m_allocatedSize;
}
