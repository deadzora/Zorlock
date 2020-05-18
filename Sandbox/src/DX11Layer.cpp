#include "DX11Layer.h"
#include "imgui/imgui.h"



DX11Layer::DX11Layer() : Layer("DX11Layer"), m_CameraController(1280.0f / 720.0f)
{
	
	

}

void DX11Layer::OnAttach()
{
}

void DX11Layer::OnDetach()
{
}

void DX11Layer::OnUpdate(Zorlock::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Zorlock::RenderCommand::SetClearColor({ 0.1f, 1.0f, 1.0f, 1 });
	Zorlock::RenderCommand::Clear();

	Zorlock::Renderer::BeginScene(m_CameraController.GetCamera());


	Zorlock::Renderer::EndScene();
}

void DX11Layer::OnImGuiRender()
{
	ImGui::Begin("test");
	ImGui::Text("This is example text");
	ImGui::Button("Click Me!");
	ImGui::SameLine();
	std::string clickcount = "You're mom ";
	ImGui::Text(clickcount.c_str());
	ImGui::End();
}

void DX11Layer::OnEvent(Zorlock::Event& e)
{
}
