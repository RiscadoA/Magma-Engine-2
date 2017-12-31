#include "String.hpp"

bool Magma::String::StartsWith(const std::string & string, const std::string & start)
{
	if (string.size() < start.size())
		return false;
		return string.substr(0, start.size()) == start;
}

bool Magma::String::EndsWith(const std::string & string, const std::string & end)
{
	if (string.size() < end.size())
		return false;
	return string.substr(string.size() - end.size(), end.size()) == end;
}

std::vector<std::string> Magma::String::Split(const std::string & string, const std::string & delim)
{
	std::vector<std::string> vec;
	vec.push_back("");
	for (size_t i = 0, s = string.size(); i < s; ++i)
	{
		if (s - i >= delim.size() && string.substr(i, delim.size()) == delim)
		{
			i += delim.size() - 1;
			vec.push_back("");
		}
		else vec.back().push_back(string[i]);
	}
	if (vec.size() > 1)
		if (vec.back().empty())
			vec.pop_back();
	return vec;
}
