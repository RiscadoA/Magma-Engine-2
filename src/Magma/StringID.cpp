#include "StringID.hpp"

#include <stdexcept>
#include <string>
#include <algorithm>

using namespace Magma;

const StringID & StringID::Get(const char * string)
{
	auto thisID = std::hash<std::string>()(string);

	auto ptr = s_first;
	while (ptr != nullptr)
	{
		if (thisID == ptr->m_id)
		{
#ifdef _DEBUG
			if (strcmp(ptr->m_string, string))
				throw std::runtime_error("Failed to get SID from string, collision between strings \"" + std::string(ptr->m_string) + "\" and \"" + std::string(string) + "\"");
#endif
			return *ptr;
		}
		ptr = ptr->m_next;
	}

	if (s_first == nullptr)
	{
		s_first = new StringID();
		s_last = s_first;
	}
	else
	{
		s_last->m_next = new StringID();
		s_last = s_last->m_next;
	}

	s_last->m_next = nullptr;
	s_last->m_string = _strdup(string);
	s_last->m_id = thisID;

	return *s_last;
}

const char * StringID::Get(const StringID & sid)
{
	return sid.m_string;
}

void StringID::Clear()
{
	auto ptr = s_first;
	while (ptr != nullptr)
	{
		auto prev = ptr;
		ptr = ptr->m_next;

		free((void*)prev->m_string);
		delete prev;
	}
	s_first = nullptr;
	s_last = nullptr;
}

bool Magma::StringID::operator==(const char * string) const
{
	return m_id == std::hash<std::string>()(string);
}

bool Magma::StringID::operator==(const StringID & sid) const
{
	return m_id == sid.m_id;
}
