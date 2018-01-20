#pragma once

#include <vector>
#include <string>

#include "../Serializable.hpp"

namespace Magma
{
	class CSVDocument : public Serializable
	{
	public:
		static const int MajorVersion = 1;
		static const int MinorVersion = 0;
		
		/// <summary>
		///		Adds a field to the last record
		/// </summary>
		inline void AddField(const std::wstring& field) { if (m_data.empty()) m_data.push_back({}); m_data.back().push_back(field); }

		/// <summary>
		///		Adds a record to this document
		/// </summary>
		inline void AddRecord(const std::vector<std::wstring>& record) { m_data.push_back(record); }

		/// <summary>
		///		Clears this document
		/// </summary>
		inline void Clear() { m_data.clear(); }

		/// <summary>
		///		Gets the records loaded in this document
		/// </summary>
		inline const auto& GetData() { return m_data; }

	private:
		std::vector<std::vector<std::wstring>> m_data;

		// Inherited via Serializable
		virtual void Serialize(std::wostream & stream) const override;
		virtual void Deserialize(std::wistream & stream) override;

	};
}