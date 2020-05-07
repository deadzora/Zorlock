#include "ZLpch.h"
#include "Zorlock/ImGui/ImGuiLayer.h"
#include "Zorlock/Core/Application.h"
#include "Zorlock/Renderer/RendererAPI.h"
// TEMPORARY

#include <glfw3.h>
#include <glfw3native.h>
#include <glad/glad.h>
#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include <DX11Raz.h>
#include <DX11DeviceContext.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

//extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);




namespace Zorlock {

	

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ZL_PROFILE_FUNCTION();

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OpenGL:
		{
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		}
		case RendererAPI::API::DX11:
		{


		}
		}

		        // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		

		// Setup Platform/Renderer bindings
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::OpenGL:
			{
				GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
				ImGui_ImplGlfw_InitForOpenGL(window, true);
				ImGui_ImplOpenGL3_Init("#version 410");
				break;
			}
			case RendererAPI::API::DX11:
			{
				
				//ImGui_ImplWin32_Init(glfwGetWin32Window(window));
				//soon!
				
				DX11Raz::ZWindow* window = static_cast<DX11Raz::ZWindow*>(app.GetWindow().GetNativeWindow());
				ImGui_ImplWin32_Init(window->GetHWND());
				ImGui_ImplDX11_Init(DX11Raz::DX11GraphicsEngine::Get()->GetDevice(), window->GetDeviceContext()->GetContext());

			}
		}

	}

	void ImGuiLayer::OnDetach()
	{
		ZL_PROFILE_FUNCTION();
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OpenGL:
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
			break;
		}
		case RendererAPI::API::DX11:
		{
			//Soon
			//ImGui_ImplDX11_Shutdown();
			//ImGui_ImplWin32_Shutdown();		
			//ImGui::DestroyContext();
			break;
		}
		}

		
	}
	
	void ImGuiLayer::Begin()
	{
		ZL_PROFILE_FUNCTION();

		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::OpenGL:
			{
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();
				break;
			}
			case RendererAPI::API::DX11:
			{
				
				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();
				
				break;
			}
		}
		
	}

	void ImGuiLayer::End()
	{
		ZL_PROFILE_FUNCTION();



		// Rendering
		
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OpenGL:
		{
			ImGuiIO& io = ImGui::GetIO();
			Application& app = Application::Get();
			io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();

				glfwMakeContextCurrent(backup_current_context);
			}
			break;
		}
		case RendererAPI::API::DX11:
		{
			ImGuiIO& io = ImGui::GetIO();
			Application& app = Application::Get();
			io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
			ImGui::Render();

			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

			break;
		}
		}



	}

}