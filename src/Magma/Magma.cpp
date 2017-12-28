#include "Magma.hpp"

int main(int argc, char** argv)
{
	Magma::Locator locator;

	Load(locator);
	Unload(locator);

	return 0;
}