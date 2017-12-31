#pragma once

#include <string>
#include <vector>

namespace Magma
{
	namespace String
	{
		/// <summary>
		///		Checks if a string starts with another.
		/// </summary>
		/// <param name="string">String to check</param>
		/// <param name="start">String start</param>
		/// <returns>True if the string starts with the other, otherwise false</returns>
		bool StartsWith(const std::string& string, const std::string& start);

		/// <summary>
		///		Checks if a string ends with another.
		/// </summary>
		/// <param name="string">String to check</param>
		/// <param name="end">String end</param>
		/// <returns>True if the string ends with the other, otherwise false</returns>
		bool EndsWith(const std::string& string, const std::string& end);

		/// <summary>
		///		Splits a string into multiple strings using a delimiter
		/// </summary>
		/// <param name="string">String to split</param>
		/// <param name="delim">Delimiter to use</param>
		/// <returns>Split strings</returns>
		std::vector<std::string> Split(const std::string& string, const std::string& delim);
	}
}