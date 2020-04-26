#pragma once

#ifdef ZL_PLATFORM_WINDOWS

extern Zorlock::Application* Zorlock::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Zorlock::CreateApplication();
	app -> Run();
	delete app;
}

#endif