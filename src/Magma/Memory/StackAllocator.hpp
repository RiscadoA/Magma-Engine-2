#pragma once

#include "Allocator.hpp"

namespace Magma
{
	class StackAllocator final : public Allocator
	{
	public:
		StackAllocator(size_t size);
		virtual ~StackAllocator() final;

		// Inherited via Allocator
		virtual void * Allocate(size_t size) final;
		virtual void Deallocate(void * ptr) final;
		virtual size_t GetSize() final;
		virtual size_t GetAllocatedSize() final;

	private:
		size_t m_size;
		size_t m_allocatedSize;

		char* m_start;
		char* m_end;
		char* m_head;
	};
}