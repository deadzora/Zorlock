#include <Zorlock.h>
#include <Zorlock/Core/EntryPoint.h>
#include "DX11Layer.h"
#include "Sandbox2D.h"
#include "ExampleLayer.h"
#include "GraphicsTestLayer.h"

class Sandbox : public Zorlock::Application
{
public:
	Sandbox()
	{

		PushLayer(new DX11Layer());
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
