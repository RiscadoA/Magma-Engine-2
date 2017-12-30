#include "Exception.hpp"

#include <cstring>

Magma::Exception::Exception(const char * msg) noexcept
{
	m_msg = new char[strlen(msg) + 1];
	strcpy(m_msg, msg);
}

Magma::Exception::~Exception() noexcept
{
	delete[] m_msg;
}

const char * Magma::Exception::What() const noexcept
{
	return m_msg;
}
