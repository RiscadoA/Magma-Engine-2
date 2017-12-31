#pragma once

#include <memory>

namespace Magma
{
	class Settings;

	struct Locator
	{
		std::shared_ptr<Settings> settings;
	};
}