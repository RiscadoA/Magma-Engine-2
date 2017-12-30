#pragma once

#pragma once

#include <string>
#include <list>
#include <map>
#include <memory>

#include "..\Serializable.hpp"
#include "Exception.hpp"

namespace Magma
{
	/// <summary>
	///		Allows XML Documents to be read/written from/to streams
	/// </summary>
	class XMLDocument final : public Serializable
	{
	public:
		static const size_t MajorVersion = 1;
		static const size_t MinorVersion = 0;

		XMLDocument();
		~XMLDocument();

		/// <summary>
		///		Represents a node in this document
		/// </summary>
		class Node
		{
		public:
			~Node() = default;

			/// <summary>
			///		Sets this node name.
			/// </summary>
			/// <param name="name">Node name</param>
			void SetName(const std::string& name);

			/// <summary>
			///		Gets this node name.
			/// </summary>
			/// <returns>This node name</returns>
			const std::string& GetName() const;

			/// <summary>
			///		Gets this node ID.
			/// </summary>
			/// <returns>This node iD</returns>
			size_t GetID() const;

			/// <summary>
			///		Adds a child to this node.
			/// </summary>
			/// <param name="name">Child name</param>
			/// <returns>Reference to child</returns>
			Node& AddChild(const std::string& name);

			/// <summary>
			///		Gets the first child found with a name.
			/// </summary>
			/// <exception cref="ElementNotFoundException">Thrown when this node doesn't contain a child with this name</exception>
			/// <param name="name">Name to check</param>
			/// <returns>First child found</returns>
			Node& GetChild(const std::string& name);

			/// <summary>
			///		Gets a child from its ID.
			/// </summary>
			/// <exception cref="ElementNotFoundException">Thrown when this node doesn't contain a child with this ID</exception>
			/// <param name="id">Child ID</param>
			/// <returns>Child</returns>
			Node& GetChild(size_t id);

			/// <summary>
			///		Gets all children that share a common name.
			/// </summary>
			/// <param name="name">Name to check</param>
			/// <returns>Children with name</returns>
			std::list<std::reference_wrapper<Node>> GetChildren(const std::string& name);

			/// <summary>
			///		Gets all children this node has.
			/// </summary>
			/// <returns>All children this node has</returns>
			std::list<std::reference_wrapper<Node>> GetChildren();

			/// <summary>
			///		Removes a child from its ID.
			/// </summary>
			/// <exception cref="ElementNotFoundException">Thrown when this node doesn't contain a child with this ID</exception>
			/// <param name="childID">Child id</param>
			void RemoveChild(size_t childID);

			/// <summary>
			///		Removes all children from this node.
			/// </summary>
			void ClearChildren();

			/// <summary>
			///		Removes an attribute from this node.
			/// </summary>
			/// <exception cref="ElementNotFoundException">Thrown when this node doesn't contain an attribute with this name</exception>
			/// <param name="name">Attribute name</param>
			void RemoveAttribute(const std::string& name);

			/// <summary>
			///		Sets or adds an attribute in this node.
			/// </summary>
			/// <param name="name">Attribute name</param>
			/// <param name="value">Attribute value</param>
			void SetAttribute(const std::string& name, const std::string& value);

			/// <summary>
			///		Gets an attribute from its name.
			/// </summary>
			/// <exception cref="ElementNotFoundException">Thrown when this node doesn't contain an attribute with this name</exception>
			/// <param name="name">Attribute name</param>
			/// <returns>Attribute value</returns>
			const std::string& GetAttribute(const std::string& name) const;

			/// <summary>
			///		Gets all attributes this node has.
			/// </summary>
			/// <returns>All attributes this node has</returns>
			const std::map<std::string, std::string>& GetAttributes() const;

			/// <summary>
			///		Calls Node::SetAttribute for each attribute.
			/// </summary>
			/// <param name="attributes">Attributes to set</param>
			void SetAttributes(const std::map<std::string, std::string> attributes);

			/// <summary>
			///		Removes all attributes from this node.
			/// </summary>
			void ClearAttributes();

			/// <summary>
			///		Gets the text present in this node
			/// </summary>
			/// <returns>The text present in this node</returns>
			const std::string& GetText() const;

			/// <summary>
			///		Sets the text present in this node
			/// </summary>
			/// <param name="text">Text</param>
			void SetText(const std::string& text);

		private:
			friend class XMLDocument;

			Node(XMLDocument& document, std::string name, size_t id);

			XMLDocument& m_document;
			size_t m_id;
			std::string m_name;
			std::string m_text;
			std::map<std::string, std::string> m_attributes;
			std::list<std::shared_ptr<Node>> m_children;
		};

		/// <summary>
		///		Gets this document's root.
		/// </summary>
		/// <returns>This document's root</returns>
		Node& GetRoot();

		/// <summary>
		///		Clears this document.
		/// </summary>
		void Clear();

		/// <summary>
		///		Gets the next node ID.
		/// </summary>
		/// <returns></returns>
		size_t GetNextNodeID();

	private:
		size_t m_nextNodeID;
		std::shared_ptr<Node> m_rootNode;

		// Inherited via Serializable
		virtual void Serialize(std::ostream & stream) const final;
		virtual void Deserialize(std::istream & stream) final;
	};
}