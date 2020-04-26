#pragma once

#include "core.h"

namespace Zorlock
{
	class ZORLOCK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client
	Application* CreateApplication();
}
