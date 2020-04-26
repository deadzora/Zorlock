#pragma once

#ifdef ZL_PLATFORM_WINDOWS

extern Zorlock::Application* Zorlock::CreateApplication();

int main(int argc, char** argv)
{
	Zorlock::Log::Init();
	ZL_CORE_WARN("Initialized Log!");
	ZL_INFO("Welcome to Zorlock Engine!");
	auto app = Zorlock::CreateApplication();
	app -> Run();
	delete app;
}

#endif