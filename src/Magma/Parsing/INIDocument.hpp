#pragma once

#include <map>
#include <string>

#include "../Serializable.hpp"

namespace Magma
{
	class INIDocument : public Serializable
	{
	public:
		static const int MajorVersion = 1;
		static const int MinorVersion = 0;

		inline void SetKey(const std::wstring value, const std::wstring& field, const std::wstring& section = L"");
		inline void SetSection(const std::wstring& sectionName, const std::map<std::wstring, std::wstring>& section);
		inline const std::wstring& GetKey(const std::wstring& name, const std::wstring& section = L"");
		inline const std::map<std::wstring, std::wstring>& GetSection(const std::wstring& section = L"");
		inline void Clear();
		inline const auto& GetData();

	private:
		std::map<std::wstring, std::map<std::wstring, std::wstring>> m_data;

		// Inherited via Serializable
		virtual void Serialize(std::wostream & stream) const override;
		virtual void Deserialize(std::wistream & stream) override;

	};
}

inline void Magma::INIDocument::SetKey(const std::wstring value, const std::wstring & field, const std::wstring & section)
{
	m_data[section][value] = field;
}

inline void Magma::INIDocument::SetSection(const std::wstring & sectionName, const std::map<std::wstring, std::wstring>& section)
{
	m_data[sectionName] = section;
}

inline const std::wstring & Magma::INIDocument::GetKey(const std::wstring & name, const std::wstring & section)
{
	return m_data[section][name];
}

inline const std::map<std::wstring, std::wstring>& Magma::INIDocument::GetSection(const std::wstring & section)
{
	return m_data[section];
}

inline void Magma::INIDocument::Clear()
{
	m_data.clear();
}

inline const auto & Magma::INIDocument::GetData()
{
	return m_data;
}

