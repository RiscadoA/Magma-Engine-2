#include <iostream>
#include <fstream>

#include <Magma\Magma.hpp>
#include <Magma\Parsers\CSVDocument.hpp>
#include <Magma\Exception.hpp>

using namespace Magma;

void Load(Locator& locator)
{
	std::cout << "Load" << std::endl;

	CSVDocument document;

	try
	{
		{
			std::ifstream file("test2.csv");
			if (!file.is_open())
			{
				std::cout << "Failed to read from file" << std::endl;
				return;
			}
			file >> document;
			file.close();
		}

		auto data = document.GetData();
		for (auto& record : data)
		{
			for (auto& field : record)
				std::cout << "{\"" << field << "\"},";
			std::cout << std::endl;
		}

		{
			std::ofstream file2("test3.csv");
			if (!file2.is_open())
			{
				std::cout << "Failed to write to file" << std::endl;
				return;
			}
			file2 << document;
			file2.close();
		}
	}
	catch (const Exception& e)
	{
		std::cout << e.What() << std::endl;
	}
}

void Unload(Locator& locator)
{
	std::cout << "Unload" << std::endl;
	std::cin.get();
}
