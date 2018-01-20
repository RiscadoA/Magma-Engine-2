#include "StackAllocator.hpp"

Magma::StackAllocator::StackAllocator(size_t size)
{
	m_size = size;
	m_allocatedSize = 0;
	m_start = (char*)malloc(m_size);
	m_end = m_start + m_size;
	m_head = m_start;

	std::wcout << L"Constructed stack allocator with size " << m_size << std::endl;
}

Magma::StackAllocator::~StackAllocator()
{
	if (m_allocatedSize != 0)
		std::wcerr << L"Warning: stack allocator destroyed while there were still objects allocated in it" << std::endl;

	std::wcout << L"Deconstructed stack allocator with size " << m_size << std::endl;

	free(m_start);
	m_start = nullptr;
	m_end = nullptr;
	m_head = nullptr;
}

void * Magma::StackAllocator::Allocate(size_t size)
{
	if (m_head + size >= m_end)
		return nullptr;
	auto alloc = m_head;
	m_head += size;
	m_allocatedSize = m_head - m_start;
	return alloc;
}

void Magma::StackAllocator::Deallocate(void * ptr)
{
	if (m_head > (char*)ptr)
	{
		m_head = reinterpret_cast<char*>(ptr);
		m_allocatedSize = m_head - m_start;
	}
}

size_t Magma::StackAllocator::GetSize()
{
	return m_size;
}

size_t Magma::StackAllocator::GetAllocatedSize()
{
	return m_allocatedSize;
}
