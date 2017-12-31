#pragma once

#include "..\Exception.hpp"

namespace Magma
{
	/// <summary>
	///		Thrown when an element is not found
	/// </summary>
	class ElementNotFoundException : public Exception
	{
	public:
		inline ElementNotFoundException(const char* msg) : Exception(msg) {}
	};
}