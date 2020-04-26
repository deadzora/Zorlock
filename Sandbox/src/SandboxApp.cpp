#include <Zorlock.h>

class Sandbox : public Zorlock::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Zorlock::Application* Zorlock::CreateApplication()
{
	return new Sandbox();
}