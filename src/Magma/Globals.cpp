#include "Globals.hpp"

std::map<std::string, Magma::Globals::GlobalVariable> Magma::Globals::m_variables = {};

Magma::Globals::GlobalVariable & Magma::Globals::Get(const std::string & name)
{
	return m_variables[name];
}

void Magma::Globals::GlobalVariable::Serialize(std::ostream & stream) const
{
	stream << "?{" << m_value << "}?";
}

void Magma::Globals::GlobalVariable::Deserialize(std::istream & stream)
{
	stream.ignore(64, ' ');
	if (stream.get() != '?' && stream.get() != '{')
		throw FailedToDeserializeException("Failed to deserialize global variable, invalid header");

	char c = '\0';
	while ((c = stream.get()) != -1)
	{
		if (c == '}' && stream.peek() == '?')
		{
			stream.get();
			break;
		}
		else m_value += c;
	}
}
