#include "Magma.hpp"
#include "Globals.hpp"
#include "Parsers\INIDocument.hpp"
#include "Parsers\String.hpp"

#include <iostream>

using namespace Magma;

const std::string GlobalSettingsPath = "settings.ini";

int main(int argc, char** argv)
{
	Locator locator;

	// Read global settings
	try
	{
		INIDocument document;
		document.ReadFromFile(GlobalSettingsPath);

		auto sections = document.GetSections();
		for (auto& section : sections)
		{
			auto entries = document.GetEntries(section);
			for (auto& entry : entries)
				Globals::Get("Settings." + ((section.empty()) ? entry.key : (section + "." + entry.key))) << entry.value;
		}
	}
	catch (const std::ifstream::failure& e)
	{
		std::cout << "Failed to read from global settings file \"" << GlobalSettingsPath << "\"" << std::endl << e.what() << std::endl;
	}
	catch (const FailedToDeserializeException& e)
	{
		std::cout << "Failed to deserialize global settings" << std::endl << e.What() << std::endl;
	}

	Load(locator);
	Unload(locator);

	// Write global settings
	try
	{
		INIDocument document;

		auto& globals = Globals::Get();
		for (auto& g : globals)
		{
			auto split = String::Split(g.first, ".");
			if (split[0] == "Settings")
			{
				INIDocument::Entry entry;
				entry.value = g.second.GetRaw();
				if (split.size() >= 3)
				{
					entry.section = split[1];
					for (size_t i = 2; i < split.size(); ++i)
						entry.key += split[i] + '.';
					entry.key.pop_back();
				}
				else if (split.size() == 2)
				{
					entry.section = "";
					entry.key = split[1];
				}
				document.SetEntry(entry);
			}
		}

		document.WriteToFile(GlobalSettingsPath);
	}
	catch (const std::ofstream::failure& e)
	{
		std::cout << "Failed to write to global settings file \"" << GlobalSettingsPath << "\"" << std::endl << e.what() << std::endl;
	}
	catch (const FailedToSerializeException& e)
	{
		std::cout << "Failed to serialize global settings" << std::endl << e.What() << std::endl;
	}

	return 0;
}