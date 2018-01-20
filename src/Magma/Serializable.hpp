#pragma once

#include "Exception.hpp"

#include <fstream>
#include <string>

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
		inline void ReadFromFile(const std::wstring& path)
		{
			std::wifstream ifs;
			ifs.exceptions(std::wifstream::failbit | std::wifstream::badbit);
			ifs.open(path);
			this->Deserialize(ifs);
		}

		/// <summary>
		///		Writes this serializable to a file
		/// </summary>
		/// <exception cref="std::ofstream::failure">Thrown when file fails to open</exception>
		/// <exception cref="FailedToSerializeException">Thrown when object fails to serialize</exception>
		/// <param name="path">File path</param>
		inline void WriteToFile(const std::wstring& path)
		{
			std::wofstream ofs;
			ofs.exceptions(std::wofstream::failbit | std::wofstream::badbit);
			ofs.open(path);
			this->Serialize(ofs);
		}

	private:
		friend inline std::wostream& operator<<(std::wostream& stream, const Serializable& serializable)
		{
			serializable.Serialize(stream);
			return stream;
		}

		friend inline std::wistream& operator>>(std::wistream& stream, Serializable& serializable)
		{
			serializable.Deserialize(stream);
			return stream;
		}

		virtual void Serialize(std::wostream& stream) const = 0;
		virtual void Deserialize(std::wistream& stream) = 0;
	};
}