#include <Zorlock.h>
#include <Zorlock/Core/EntryPoint.h>
#include "Sandbox2D.h"
#include "ExampleLayer.h"
#include "ZorlockEditor.h"
#include "SceneLayer.h"

class Sandbox : public Zorlock::Application
{
public:
	Sandbox()
	{
		PushLayer(new ZorlockEditor());
		//PushLayer(new Sandbox2D());
		//PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Zorlock::Application* Zorlock::CreateApplication()
{
	return new Sandbox();
}
