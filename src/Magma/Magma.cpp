#include "Magma.hpp"

#include <iostream>

#include <fcntl.h>
#include <io.h>

#include "StringID.hpp"

using namespace Magma;

const std::string GlobalSettingsPath = "settings.ini";

int main(int argc, char** argv)
{
	_setmode(_fileno(stdout), _O_U8TEXT);
	std::cout.rdbuf(nullptr);

	Locator locator;

	Load(locator);
	Unload(locator);

	return 0;
}