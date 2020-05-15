#include <Zorlock.h>
#include <Zorlock/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"
#include "GraphicsTestLayer.h"

class Sandbox : public Zorlock::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new GraphicsTestLayer());
	}

	~Sandbox()
	{
	}
};

Zorlock::Application* Zorlock::CreateApplication()
{
	return new Sandbox();
}
