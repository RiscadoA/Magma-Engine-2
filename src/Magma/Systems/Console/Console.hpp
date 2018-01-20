#pragma once

#include <iostream>

namespace Magma
{
	class Console : public std::wiostream
	{
	public:
		Console();
		virtual ~Console();



	private:
		virtual void Print(const std::wstring& str) = 0;
		virtual char GetChar() = 0;
	};
}