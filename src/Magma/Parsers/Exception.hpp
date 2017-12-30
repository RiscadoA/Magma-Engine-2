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

	/// <summary>
	///		Thrown when parsing fails
	/// </summary>
	class ParsingException : public Exception
	{
	public:
		inline ParsingException(const char* msg) : Exception(msg) {}
	};
}