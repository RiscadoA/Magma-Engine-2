#pragma once

#include <iostream>

#include "Exception.hpp"

namespace Magma
{
	/// <summary>
	///		Thrown when a object serialization fails
	/// </summary>
	class FailedToSerializeException : public Exception
	{
	public:
		inline FailedToSerializeException(const char* msg) : Exception(msg) {}
	};

	/// <summary>
	///		Thrown when a object deserialization fails
	/// </summary>
	class FailedToDeserializeException : public Exception
	{
	public:
		inline FailedToDeserializeException(const char* msg) : Exception(msg) {}
	};

	/// <summary>
	///		Allows derived classes to be serialized and deserialized from streams
	/// </summary>
	class Serializable
	{
	public:
		virtual void Serialize(std::ostream& stream) const = 0;
		virtual void Deserialize(std::istream& stream) = 0;

		friend inline std::ostream& operator<<(std::ostream& stream, const Serializable& serializable)
		{
			serializable.Serialize(stream);
			return stream;
		};

		friend inline std::istream& operator>>(std::istream& stream, Serializable& serializable)
		{
			serializable.Deserialize(stream);
			return stream;
		};
	};
}