#pragma once

#include <string>
#include <deque>

#include "..\Serializable.hpp"
#include "Exception.hpp"

namespace Magma
{
	/// <summary>
	///		Allows INI Documents to be read/written from/to streams
	/// </summary>
	class INIDocument final : public Serializable
	{
	public:
		static const size_t MajorVersion = 1;
		static const size_t MinorVersion = 1;

		/// <summary>
		///		Contains info about an entry in a INI document
		/// </summary>
		struct Entry
		{
			std::string region;
			std::string key;
			std::string value;
		};

		/// <summary>
		///		Returns the entry with the key.
		///		Throws KeyNotFoundException when no entry is found with the key sent.
		/// </summary>
		const INIDocument::Entry& GetEntry(const std::string& region, const std::string& key) const;

		/// <summary>
		///		Adds or replaces an entry in this document.
		/// </summary>
		void SetEntry(Entry entry);

		/// <summary>
		///		Removes an entry from this document, using its key and region.
		/// </summary>
		void RemoveEntry(const std::string& region, const std::string& key);

		/// <summary>
		///		Gets all entries in this document.
		/// </summary>
		const std::deque<Entry>& GetEntries() const;

		/// <summary>
		///		Gets all entries in a region.
		/// </summary>
		/// <param name="region">Region to get entries from</param>
		std::deque<Entry> GetEntries(const std::string& region) const;

		/// <summary>
		///		Gets all regions in this document.
		/// </summary>
		std::deque<std::string> GetRegions() const;

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