#pragma once

#include <string>

namespace Magma
{
	/// <summary>
	///		Represents a string ID
	/// </summary>
	class StringID
	{
	public:
		static inline const StringID& Get(const std::string& string) { return StringID::Get(string.c_str()); }

		static const StringID& Get(const char* string);

		static const char* Get(const StringID& sid);

		static void Clear();

		bool operator==(const char* string) const;
		bool operator==(const StringID& sid) const;

	private:
		inline static StringID* s_first = nullptr;
		inline static StringID* s_last = nullptr;

		StringID * m_next;
		
		const char* m_string;
		size_t m_id;
	};
}