#pragma once

namespace Magma
{
	/// <summary>
	///		Magma exception base class
	/// </summary>
	class Exception
	{
	public:
		/// <summary>
		///		Constructs an exception
		/// </summary>
		/// <param name="msg">Message containing exception info</param>
		Exception(const char* msg) noexcept;
		virtual ~Exception() noexcept;

		/// <summary>
		///		Gets this exception's message
		/// </summary>
		virtual const char* What() const noexcept;

	private:
		char* m_msg;
	};

	class OutOfBoundsException : public Exception { public: using Exception::Exception; };
}