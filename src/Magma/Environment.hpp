#pragma once

#include "Memory/Allocator.hpp"

#include <memory>
#include <stack>

namespace Magma
{
	class detail_Environment
	{
	public:
		static void Push();
		static void Pop();

		std::shared_ptr<Allocator> Allocator = std::make_shared<StandardAllocator>();

	private:
		static thread_local inline std::stack<detail_Environment> s_envStack = {};
	};

	extern thread_local detail_Environment Environment;
}