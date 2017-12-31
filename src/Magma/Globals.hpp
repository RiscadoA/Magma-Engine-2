#pragma once

#include "Exception.hpp"
#include "Serializable.hpp"

#include <map>
#include <string>
#include <sstream>

namespace Magma
{
	class WrongTypeException : public Exception { using Exception::Exception; };

	/// <summary>
	///		Class used to manage globals
	/// </summary>
	class Globals
	{
	public:
		Globals() = delete;
		~Globals() = delete;

		/// <summary>
		///		Global variable class, variant type
		/// </summary>
		class GlobalVariable : public Serializable
		{
		public:
			template <typename T>
			GlobalVariable& operator<<(const T& serializable);
			template <typename T>
			GlobalVariable& operator>>(T& serializable) const;

			/// <summary>
			///		Gets the raw string this global variable uses to store data
			/// </summary>
			/// <returns>String</returns>
			inline const std::string& GetRaw() const { return m_value; }

		private:
			std::string m_value;

			// Inherited via Serializable
			virtual void Serialize(std::ostream & stream) const override;
			virtual void Deserialize(std::istream & stream) override;
		};

		/// <summary>
		///		Gets a global variable from its name
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		static GlobalVariable& Get(const std::string& name);

		/// <summary>
		///		Gets all global variables
		/// </summary>
		/// <returns>All global variables</returns>
		inline static const auto& Get() { return m_variables; }

	private:
		static std::map<std::string, GlobalVariable> m_variables;
	};

	template<typename T>
	inline Globals::GlobalVariable & Globals::GlobalVariable::operator<<(const T & serializable)
	{
		std::stringstream ss;
		ss.exceptions(std::ios::failbit);
		ss << serializable;
		m_value = ss.str();
		return *this;
	}

	template<typename T>
	inline Globals::GlobalVariable & Globals::GlobalVariable::operator>>(T & serializable) const
	{
		try
		{
			std::stringstream ss(m_value);
			ss.exceptions(std::ios::failbit);
			ss >> serializable;
		}
		catch (std::stringstream::failure& e)
		{
			throw WrongTypeException("Failed to extract value from global variable, wrong type (deserialization failed)");
		}
		return *this;
	}
}