#include "GraphicsTestLayer.h"
#include "imgui/imgui.h"

GraphicsTestLayer::GraphicsTestLayer() : Layer("Graphics Test"), m_CameraController(1280.0f / 720.0f)
{
	Zorlock::ZLSLParser parser;

	parser.Parse("assets/shaders/Texture.zlsl");
	std::string glslshader = parser.GetShader(Zorlock::ZLSLParser::OutPutShaderType::HLSL, Zorlock::ZLSLParser::ShaderSection::FRAGMENTSHADER);
	parser.SaveShader(glslshader, "../testpixel.hlsl");
}

void GraphicsTestLayer::OnAttach()
{
}

void GraphicsTestLayer::OnDetach()
{
}

void GraphicsTestLayer::OnUpdate(Zorlock::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Zorlock::RenderCommand::SetClearColor({ 0.1f, 1.0f, 1.0f, 1 });
	Zorlock::RenderCommand::Clear();

	Zorlock::Renderer::BeginScene(m_CameraController.GetCamera());


	Zorlock::Renderer::EndScene();
}

void GraphicsTestLayer::OnImGuiRender()
{
	ImGui::Begin("test");
	ImGui::Text("This is example text");
	ImGui::Button("Click Me!");
	ImGui::SameLine();
	std::string clickcount = "You're mom ";
	ImGui::Text(clickcount.c_str());
	ImGui::End();
}

void GraphicsTestLayer::OnEvent(Zorlock::Event& e)
{
}
