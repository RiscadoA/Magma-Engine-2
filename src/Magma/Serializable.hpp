#pragma once

#include <fstream>

#include "Exception.hpp"

namespace Magma
{
	/// <summary>
	///		Thrown when an object's serialization fails
	/// </summary>
	class FailedToSerializeException : public Exception
	{
	public:
		inline FailedToSerializeException(const char* msg) : Exception(msg) {}
	};

	/// <summary>
	///		Thrown when an object's deserialization fails
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
		/// <summary>
		///		Reads this serializable from a file
		/// </summary>
		/// <exception cref="std::ifstream::failure">Thrown when file fails to open</exception>
		/// <exception cref="FailedToDeserializeException">Thrown when object fails to deserialize</exception>
		/// <param name="path">File path</param>
		inline void ReadFromFile(const std::string& path)
		{
			std::ifstream ifs;
			ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			ifs.open(path);
			this->Deserialize(ifs);
		}

		/// <summary>
		///		Writes this serializable to a file
		/// </summary>
		/// <exception cref="std::ofstream::failure">Thrown when file fails to open</exception>
		/// <exception cref="FailedToSerializeException">Thrown when object fails to serialize</exception>
		/// <param name="path">File path</param>
		inline void WriteToFile(const std::string& path)
		{
			std::ofstream ofs;
			ofs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			ofs.open(path);
			this->Serialize(ofs);
		}

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

	private:
		virtual void Serialize(std::ostream& stream) const = 0;
		virtual void Deserialize(std::istream& stream) = 0;
	};
}