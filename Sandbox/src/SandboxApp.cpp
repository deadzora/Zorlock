#include <Zorlock.h>
#include <Zorlock/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Zorlock::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Zorlock::Application* Zorlock::CreateApplication()
{
	return new Sandbox();
}
