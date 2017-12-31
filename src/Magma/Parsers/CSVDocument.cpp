#include "CSVDocument.hpp"

#include <regex>

void Magma::CSVDocument::AddRecord(const std::deque<std::string>& record)
{
	m_data.push_back(record);
}

void Magma::CSVDocument::AddField(const std::string & field)
{
	if (m_data.empty())
		m_data.emplace_back();
	m_data.back().push_back(field);
}

void Magma::CSVDocument::Clear()
{
	m_data.clear();
}

void Magma::CSVDocument::Serialize(std::ostream & stream) const
{
	stream << "?MCSV " << MajorVersion << "." << MinorVersion << std::endl;

	auto makeValid = [](const std::string& str) -> std::string
	{
		bool needsQuotes = false;
		std::string ret = "";

		for (size_t i = 0; i < str.size(); ++i)
			if (str[i] == '\n' || str[i] == '"')
			{
				needsQuotes = true;
				break;
			}

		if (needsQuotes)
			ret += "\"";

		for (size_t i = 0; i < str.size(); ++i)
		{
			if (str[i] == '"')
				ret += "\"\"";
			else
				ret += str[i];
		}

		if (needsQuotes)
			ret += "\"";

		return ret;
	};

	for (auto& record : m_data)
	{
		for (auto it = record.begin(); it != record.end(); ++it)
		{
			if (it == record.end() - 1)
				stream << makeValid(*it) << std::endl;
			else
				stream << makeValid(*it) << ",";
		}
	}

	stream << "?end" << std::endl;
}

void Magma::CSVDocument::Deserialize(std::istream & stream)
{
	m_data.clear();

	std::regex versionRegex(R"(\?MCSV (\d+)\.(\d+))");
	std::smatch match;

	std::string line;
	std::getline(stream, line);
	if (!std::regex_search(line, match, versionRegex))
		throw FailedToDeserializeException(("Failed to deserialize MCSV document, invalid header \"" + line + "\"").c_str());
	if (MajorVersion != std::stoull(match.str(1)) || MinorVersion < std::stoull(match.str(2)))
		throw FailedToDeserializeException(("Failed to deserialize MCSV document, document version " + match.str(1) + "." + match.str(2) + " not supported (current version is " + std::to_string(MajorVersion) + "." + std::to_string(MinorVersion) + ")").c_str());

	{
		std::deque<std::string> record;
		std::string value;
		char character = '\0';
		char prevCharacter = '\0';
		bool inQuotes = false;
		bool escapeQuotes = false;
		while ((character = stream.get()) != -1)
		{
			if (prevCharacter == '\n' && character == '?')
			{
				// Special function
				std::string function;
				while ((stream >> character) && character != '\n')
					function += character;
				if (function == "end")
					break;
				else
					throw FailedToDeserializeException(("Failed to parse MCSV document, unknown special function \"?" + function + "\"").c_str());
			}
			else if (inQuotes == false && character == ',')
			{
				record.push_back(value);
				value.clear();
			}
			else if (inQuotes == false && character == '\n')
			{
				if (value != "")
				{
					record.push_back(value);
					value = "";
				}

				if (!record.empty())
				{
					m_data.push_back(record);
					record.clear();
				}
			}
			else if (escapeQuotes == false && character == '"' && stream.peek() != '"')
			{
				inQuotes = !inQuotes;
			}
			else if (escapeQuotes == false && character == '"' && stream.peek() == '"')
				escapeQuotes = true;
			else
			{
				value += character;
				escapeQuotes = false;
			}

			prevCharacter = character;
		}
		if (value != "")
			record.push_back(value);
		if (!record.empty())
			m_data.push_back(record);
	}


}
