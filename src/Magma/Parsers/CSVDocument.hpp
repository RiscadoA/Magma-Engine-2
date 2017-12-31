#pragma once

#include <string>
#include <deque>

#include "..\Serializable.hpp"
#include "ParserException.hpp"

namespace Magma
{
	/// <summary>
	///		Allows CSV Documents to be read/written from/to streams
	/// </summary>
	class CSVDocument final : public Serializable
	{
	public:
		static const size_t MajorVersion = 1;
		static const size_t MinorVersion = 0;

		/// <summary>
		///		Gets the CSV data loaded from this document
		/// </summary>
		/// <returns>Data loaded from this document</returns>
		inline const std::deque<std::deque<std::string>>& GetData() const { return m_data; }

		/// <summary>
		///		Adds a record to this document.
		/// </summary>
		/// <param name="record">Record to be added</param>
		void AddRecord(const std::deque<std::string>& record);

		/// <summary>
		///		Adds a field to the last record in this document.
		/// </summary>
		/// <param name="field">Field to be added</param>
		void AddField(const std::string& field);

		/// <summary>
		///		Clears this document.
		/// </summary>
		void Clear();

	private:
		std::deque<std::deque<std::string>> m_data;

		// Inherited via Serializable
		virtual void Serialize(std::ostream & stream) const override;
		virtual void Deserialize(std::istream & stream) override;
	};
}