#pragma once
#include "core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"

#include "Zorlock/ImGui/ImGuiLayer.h"

namespace Zorlock
{
	class ZORLOCK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}
