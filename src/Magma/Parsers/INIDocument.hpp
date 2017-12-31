#pragma once

#include <string>
#include <deque>
#include <set>

#include "..\Serializable.hpp"
#include "ParserException.hpp"

namespace Magma
{
	/// <summary>
	///		Allows INI Documents to be read/written from/to streams
	/// </summary>
	class INIDocument final : public Serializable
	{
	public:
		static const size_t MajorVersion = 1;
		static const size_t MinorVersion = 2;

		/// <summary>
		///		Contains info about an entry in a INI document
		/// </summary>
		struct Entry
		{
			std::string section;
			std::string key;
			std::string value;
		};

		/// <summary>
		///		Returns the entry with the key.
		///		Throws KeyNotFoundException when no entry is found with the key sent.
		/// </summary>
		const INIDocument::Entry& GetEntry(const std::string& section, const std::string& key) const;

		/// <summary>
		///		Adds or replaces an entry in this document.
		/// </summary>
		void SetEntry(Entry entry);

		/// <summary>
		///		Removes an entry from this document, using its key and section.
		/// </summary>
		void RemoveEntry(const std::string& section, const std::string& key);

		/// <summary>
		///		Gets all entries in this document.
		/// </summary>
		const std::deque<Entry>& GetEntries() const;

		/// <summary>
		///		Gets all entries in a section.
		/// </summary>
		/// <param name="section">Section to get entries from</param>
		std::deque<Entry> GetEntries(const std::string& section) const;

		/// <summary>
		///		Gets all sections in this document.
		/// </summary>
		std::set<std::string> GetSections() const;

		/// <summary>
		///		Clears this document.
		/// </summary>
		void Clear();

	private:
		std::deque<Entry> m_data;

		// Inherited via Serializable
		virtual void Serialize(std::ostream & stream) const final;
		virtual void Deserialize(std::istream & stream) final;
	};
}