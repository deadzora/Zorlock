#include <Zorlock.h>

class ExampleLayer : public Zorlock::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		ZL_INFO("ExampleLayer::Update");
	}

	void OnEvent(Zorlock::Event& event) override
	{
		ZL_TRACE("{0}", event);
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