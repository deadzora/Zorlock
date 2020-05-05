#pragma once
#include "Zorlock/Core/Core.h"

#ifdef ZL_PLATFORM_WINDOWS

extern Zorlock::Application* Zorlock::CreateApplication();

int main(int argc, char** argv)
{
	Zorlock::Log::Init();

	ZL_PROFILE_BEGIN_SESSION("Startup", "ZorlockProfile-Startup.json");
	auto app = Zorlock::CreateApplication();
	ZL_PROFILE_END_SESSION();

	ZL_PROFILE_BEGIN_SESSION("Runtime", "ZorlockProfile-Runtime.json");
	app->Run();
	ZL_PROFILE_END_SESSION();

	ZL_PROFILE_BEGIN_SESSION("Startup", "ZorlockProfile-Shutdown.json");
	delete app;
	ZL_PROFILE_END_SESSION();
}

#endif
