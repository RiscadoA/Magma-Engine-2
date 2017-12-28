#include <iostream>

#include <Magma/Magma.hpp>

void Load(Magma::Locator& locator)
{
	std::cout << "Load" << std::endl;
}

void Unload(Magma::Locator& locator)
{
	std::cout << "Unload" << std::endl;
	std::cin.get();
}
