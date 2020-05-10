#pragma once

#include "Zorlock/Core/Core.h"

#include "Zorlock/Core/Window.h"
#include "Zorlock/Core/LayerStack.h"
#include "Zorlock/Events/Event.h"
#include "Zorlock/Events/ApplicationEvent.h"

#include "Zorlock/Core/Timestep.h"

#include "Zorlock/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);



namespace Zorlock {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}