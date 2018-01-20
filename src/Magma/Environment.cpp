#include "Environment.hpp"

thread_local Magma::detail_Environment Magma::Environment = Magma::detail_Environment();

void Magma::detail_Environment::Push()
{
	s_envStack.push(Magma::Environment);
}

void Magma::detail_Environment::Pop()
{
	Magma::Environment = s_envStack.top();
	s_envStack.pop();
}
