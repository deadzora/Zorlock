#include <Zorlock.h>

#include "imgui/imgui.h"

class ExampleLayer : public Zorlock::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (Zorlock::Input::IsKeyPressed(ZL_KEY_TAB))
			ZL_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}


	void OnEvent(Zorlock::Event& event) override
	{
		if (event.GetEventType() == Zorlock::EventType::KeyPressed)
		{
			Zorlock::KeyPressedEvent& e = (Zorlock::KeyPressedEvent&)event;
			if (e.GetKeyCode() == ZL_KEY_TAB)
				ZL_TRACE("Tab Key is pressed (event)!");
			ZL_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Zorlock::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Zorlock::Application* Zorlock::CreateApplication()
{
	return new Sandbox();
}