#pragma once

#include "Core.h"

#include "Window.h"
#include "Zorlock/LayerStack.h"
#include "Zorlock/Events/Event.h"
#include "Zorlock/Events/ApplicationEvent.h"

#include "Zorlock/ImGui/ImGuiLayer.h"
#include "Zorlock/Renderer/Shader.h"
#include "Zorlock/Renderer/Buffer.h"
#include "Zorlock/Renderer/VertexArray.h"
#include "Zorlock/Renderer/ZColor.h"
#include "Zorlock/Renderer/OrthographicCamera.h"

namespace Zorlock {

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
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}