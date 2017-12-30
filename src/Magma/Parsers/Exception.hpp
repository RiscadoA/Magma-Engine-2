#pragma once

#include "..\Exception.hpp"

namespace Magma
{
	/// <summary>
	///		Thrown when a key is not found
	/// </summary>
	class KeyNotFoundException : public Exception
	{
	public:
		inline KeyNotFoundException(const char* msg) : Exception(msg) {}
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