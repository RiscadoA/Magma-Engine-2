#include <iostream>
#include <fstream>

#include <Magma\Magma.hpp>
#include <Magma\Parsers\XMLDocument.hpp>
#include <Magma\Exception.hpp>

using namespace Magma;

void Load(Locator& locator)
{
	std::cout << "Load" << std::endl;

	XMLDocument document;

	try
	{
		/*{
			document.GetRoot().SetName("database");
			auto& node = document.GetRoot().AddChild("user");
			node.SetAttribute("id", "4");
			node.AddChild("name").SetText("Ricardo Antunes");
			node.AddChild("age").SetText("15");
			node.AddChild("description").SetText("Loves programming in C++.\nCurrently working on a game engine.");
		}*/

		{
			std::ifstream file("in.xml");
			if (!file.is_open())
			{
				std::cout << "Failed to read from file" << std::endl;
				return;
			}
			file >> document;
			file.close();
		}

		std::cout << document;

		{
			std::ofstream file("out.xml");
			if (!file.is_open())
			{
				std::cout << "Failed to write to file" << std::endl;
				return;
			}
			file << document;
			file.close();
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
