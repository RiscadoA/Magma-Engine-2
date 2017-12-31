#include <iostream>
#include <fstream>

#include <Magma\Magma.hpp>
#include <Magma\Globals.hpp>

#include <Magma\Parsers\String.hpp>

using namespace Magma;

void Load(const Locator& locator)
{
	std::cout << "Load" << std::endl;

	// Print globals
	{
		auto globals = Globals::Get();
		for (auto& g : globals)
			std::cout << g.first << " = " << g.second << std::endl;
	}
}

void Unload(const Locator& locator)
{
	std::cout << "Unload" << std::endl;
	std::cin.get();
}
