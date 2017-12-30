#include "XMLDocument.hpp"

#include <functional>
#include <regex>
#include <string>
#include <sstream>
#include <stack>

Magma::XMLDocument::XMLDocument()
{
	this->Clear();
	m_nextNodeID = 1;
}

Magma::XMLDocument::~XMLDocument()
{
	m_rootNode = nullptr;
}

Magma::XMLDocument::Node & Magma::XMLDocument::GetRoot()
{
	return *m_rootNode;
}

void Magma::XMLDocument::Clear()
{
	m_rootNode = nullptr;
	m_rootNode = std::shared_ptr<Node>(new Node(*this, "root", this->GetNextNodeID()));
}

size_t Magma::XMLDocument::GetNextNodeID()
{
	return m_nextNodeID++;
}

void Magma::XMLDocument::Serialize(std::ostream & stream) const
{
	std::function<void(std::ostream&, const Node&, size_t)> serializeNode = [&serializeNode](std::ostream& stream, const Node& node, size_t indentation)
	{
		for (size_t i = 0; i < indentation; ++i)
			stream << '\t';
		stream << '<' << node.m_name;
		for (auto& attribute : node.m_attributes)
		{
			stream << ' ' << attribute.first << "=\"";

			for (auto& c : attribute.second)
			{
				if (c == '<')
					stream << "&lt;";
				else if (c == '>')
					stream << "&gt;";
				else if (c == '\'')
					stream << "&apos;";
				else if (c == '"')
					stream << "&quot;";
				else
					stream << c;
			}

			stream << '"';
		}
		stream << '>';

		bool hadNewLines = true;

		if (!node.m_text.empty())
		{
			bool hasNewLines = false;
			for (auto& c : node.m_text)
				if (c == '\n')
				{
					hasNewLines = true;
					break;
				}

			if (hasNewLines)
			{
				stream << std::endl;
				std::stringstream ss(node.m_text);
				std::string line;
				while (std::getline(ss, line))
				{
					for (size_t i = 0; i < indentation + 1; ++i)
						stream << '\t';
					stream << line << std::endl;
				}
			}
			else
				for (auto& c : node.m_text)
				{
					if (c == '<')
						stream << "&lt;";
					else if (c == '>')
						stream << "&gt;";
					else if (c == '\'')
						stream << "&apos;";
					else if (c == '"')
						stream << "&quot;";
					else
						stream << c;
				}
			hadNewLines = hasNewLines;
		}
		else stream << std::endl;

		if (!node.m_text.empty() && !node.m_children.empty())
			throw FailedToSerializeException(("Failed to serialize MXML document, a node can't have both text and children (node \"" + node.m_name + "\")").c_str());

		for (auto& child : node.m_children)
			serializeNode(stream, *child, indentation + 1);
		if (hadNewLines)
			for (size_t i = 0; i < indentation; ++i)
				stream << '\t';
		stream << "</" << node.m_name << '>' << std::endl;
	};

	stream << "<?MXML version=\"" << MajorVersion << '.' << MinorVersion << "\"?>" << std::endl;

	serializeNode(stream, *m_rootNode, 0);
}

void Magma::XMLDocument::Deserialize(std::istream & stream)
{
	this->Clear();

	std::regex versionRegex(R""(<\?MXML version="(\d+).(\d+)" *\?>)"");
	std::regex attributesRegex(R""((\w+)="(.*?)")"");
	std::smatch match;

	std::string line;
	std::getline(stream, line);

	if (!std::regex_search(line, match, versionRegex))
		throw FailedToDeserializeException(("Failed to deserialize MXML document, invalid header \"" + line + "\"").c_str());
	if (MajorVersion != std::stoull(match.str(1)) || MinorVersion < std::stoull(match.str(2)))
		throw FailedToDeserializeException(("Failed to deserialize MXML document, document version " + match.str(1) + "." + match.str(2) + " not supported (current version is " + std::to_string(MajorVersion) + "." + std::to_string(MinorVersion) + ")").c_str());

	{
		char character = '\0';
		bool inQuotes = false;
		std::stack<std::reference_wrapper<Node>> nodes;
		size_t indentation = 0;
		size_t textIndentation = 0;
		std::string text = "";
		while ((character = stream.get()) != -1)
		{
			if (character == '<' && stream.peek() != '/') // Node start
			{
				bool hasAttributes = false;
				std::string nodeName = "";
				while (true)
				{
					character = stream.get();
					if (character == '>')
					{
						hasAttributes = false;
						break;
					}
					else if (character == ' ')
					{
						hasAttributes = true;
						break;
					}
					else nodeName += character;
				}

				if (nodes.empty())
				{
					m_rootNode = std::shared_ptr<Node>(new Node(*this, nodeName, this->GetNextNodeID()));
					nodes.push(*m_rootNode);
				}
				else
				{
					nodes.push(nodes.top().get().AddChild(nodeName));
				}

				if (hasAttributes)
				{
					std::string attributes;
					while ((character = stream.get()) != '>')
						attributes += character;

					while (std::regex_search(attributes, match, attributesRegex))
					{
						std::string name = match.str(1);
						std::string value;

						{
							std::string escapeChar = "";
							bool isEscapeChar = false;
							for (auto& c : match.str(2))
							{
								if (c == '&')
								{
									isEscapeChar = true;
									escapeChar.clear();
								}
								else if (isEscapeChar)
								{
									if (c == ';')
									{
										isEscapeChar = false;

										if (escapeChar == "lt")
											value += '<';
										else if (escapeChar == "gt")
											value += '>';
										else if (escapeChar == "apos")
											value += '\'';
										else if (escapeChar == "quot")
											value += '"';
										else
											throw FailedToDeserializeException(("Failed to deserialize MXML document, unknown escape character \"&" + escapeChar + ";\"").c_str());
									}
									else escapeChar += c;
								}
								else value += c;
							}
						}

						nodes.top().get().SetAttribute(name, value);
						attributes = match.suffix();
					}
				}

				++indentation;
				textIndentation = indentation;
			}
			else if (character == '<' && stream.peek() == '/') // Node end
			{
				std::string nodeName = "";
				stream.get();
				while (true)
				{
					character = stream.get();
					if (character == '>')
						break;
					else nodeName += character;
				}

				if (nodeName != nodes.top().get().GetName())
					throw FailedToDeserializeException(("Failed to deserialize MXML document, closing node \"" + nodeName + "\" doesn't match opening node \"" + nodes.top().get().GetName() + "\"").c_str());
				nodes.top().get().SetText(text);
				text.clear();
				nodes.pop();

				if (nodes.empty())
					break;
			}
			else
			{
				if (character == ' ' && text.empty())
					continue;
				else if (character == '\n' && text.empty())
					continue;
				else if (character == '\t' && text.empty())
					continue;
				else if (character == '\n' && !text.empty())
				{
					textIndentation = 0;
					text += character;
				}
				else if (character == '\t' && textIndentation < indentation)
					++textIndentation;
				else if (character == '&')
				{
					std::string type = "";
					while ((character = stream.get()) != ';')
						type += character;
					if (type == "lt")
						text += '<';
					else if (type == "gt")
						text += '>';
					else if (type == "apos")
						text += '\'';
					else if (type == "quot")
						text += '"';
					else
						throw FailedToDeserializeException(("Failed to deserialize MXML document, unknown escape character \"&" + type + ";\"").c_str());
				}
				else
					text += character;
			}
		}
	}
}

void Magma::XMLDocument::Node::SetName(const std::string & name)
{
	m_name = name;
}

const std::string & Magma::XMLDocument::Node::GetName() const
{
	return m_name;
}

size_t Magma::XMLDocument::Node::GetID() const
{
	return m_id;
}

Magma::XMLDocument::Node & Magma::XMLDocument::Node::AddChild(const std::string & name)
{
	auto node = std::shared_ptr<Node>(new Node(m_document, name, m_document.GetNextNodeID()));
	m_children.push_back(node);
	return *node;
}

Magma::XMLDocument::Node & Magma::XMLDocument::Node::GetChild(const std::string & name)
{
	for (auto& node : m_children)
		if (node->GetName() == name)
			return *node;
	throw ElementNotFoundException(("Couldn't get XML node's child because it hasn't a child with the name \"" + name + "\"").c_str());
}

Magma::XMLDocument::Node & Magma::XMLDocument::Node::GetChild(size_t id)
{
	for (auto& node : m_children)
		if (node->GetID() == id)
			return *node;
	throw ElementNotFoundException(("Couldn't get XML node's child because it hasn't a child with the id " + std::to_string(id)).c_str());
}

std::list<std::reference_wrapper<Magma::XMLDocument::Node>> Magma::XMLDocument::Node::GetChildren(const std::string & name)
{
	std::list<std::reference_wrapper<Node>> nodes;
	for (auto& node : m_children)
		if (node->GetName() == name)
			nodes.emplace_back(*node);
	return nodes;
}

std::list<std::reference_wrapper<Magma::XMLDocument::Node>> Magma::XMLDocument::Node::GetChildren()
{
	std::list<std::reference_wrapper<Node>> nodes;
	for (auto& node : m_children)
		nodes.emplace_back(*node);
	return nodes;
}

void Magma::XMLDocument::Node::RemoveChild(size_t childID)
{
	for (auto it = m_children.begin(); it != m_children.end(); ++it)
		if ((*it)->GetID() == childID)
		{
			m_children.erase(it);
			return;
		}
	throw ElementNotFoundException(("Couldn't remove XML node's child because it hasn't a child with the id " + std::to_string(childID)).c_str());
}

void Magma::XMLDocument::Node::ClearChildren()
{
	m_children.clear();
}

void Magma::XMLDocument::Node::RemoveAttribute(const std::string & name)
{
	auto it = m_attributes.find(name);
	if (it == m_attributes.end())
		throw ElementNotFoundException(("Couldn't remove attribute from XML node because it hasn't an attribute with the namme \"" + name + "\"").c_str());
	m_attributes.erase(it);
}

void Magma::XMLDocument::Node::SetAttribute(const std::string & name, const std::string & value)
{
	m_attributes[name] = value;
}

const std::string & Magma::XMLDocument::Node::GetAttribute(const std::string & name) const
{
	auto it = m_attributes.find(name);
	if (it == m_attributes.end())
		throw ElementNotFoundException(("Couldn't get attribute from XML node because it hasn't an attribute with the namme \"" + name + "\"").c_str());
	return it->second;
}

const std::map<std::string, std::string>& Magma::XMLDocument::Node::GetAttributes() const
{
	return m_attributes;
}

void Magma::XMLDocument::Node::SetAttributes(const std::map<std::string, std::string> attributes)
{
	for (auto& attribute : attributes)
		this->SetAttribute(attribute.first, attribute.second);
}

void Magma::XMLDocument::Node::ClearAttributes()
{
	m_attributes.clear();
}

const std::string & Magma::XMLDocument::Node::GetText() const
{
	return m_text;
}

void Magma::XMLDocument::Node::SetText(const std::string & text)
{
	m_text = text;
}

Magma::XMLDocument::Node::Node(XMLDocument & document, std::string name, size_t id)
	: m_document(document), m_name(name), m_id(id)
{

}
