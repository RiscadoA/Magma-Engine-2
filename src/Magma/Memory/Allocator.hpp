#pragma once

#include <iostream>
#include <list>

namespace Magma
{
	class Allocator
	{
	public:
		Allocator() = default;
		virtual ~Allocator() = default;

		Allocator(const Allocator&) = delete;
		Allocator(Allocator&&) = delete;
		Allocator& operator=(const Allocator&) = delete;

		virtual size_t GetSize() = 0;
		virtual size_t GetAllocatedSize() = 0;

		virtual void* Allocate(size_t size) = 0;
		virtual void Deallocate(void* ptr) = 0;
	};

	class StandardAllocator final : public Allocator
	{
	public:
		StandardAllocator() = default;
		virtual ~StandardAllocator() final;

		virtual void* Allocate(size_t size) final;
		virtual void Deallocate(void* ptr) final;

		virtual size_t GetSize() final;
		virtual size_t GetAllocatedSize() final;

	private:
		std::list<std::pair<size_t, void*>> m_allocated;
	};
}