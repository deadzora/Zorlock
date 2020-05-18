#include "GraphicsTestLayer.h"
#include "imgui/imgui.h"

GraphicsTestLayer::GraphicsTestLayer() : Layer("Graphics Test"), m_CameraController(1280.0f / 720.0f)
{
	Zorlock::ZLSLParser parser;

	parser.Parse("assets/shaders/Texture.zlsl");
	std::string glslshader = parser.GetShader(Zorlock::ZLSLParser::OutPutShaderType::GLSL, Zorlock::ZLSLParser::ShaderSection::FRAGMENTSHADER);
	parser.SaveShader(glslshader, "testpixel.glsl");
	std::string glslshaderp = parser.GetShader(Zorlock::ZLSLParser::OutPutShaderType::GLSL, Zorlock::ZLSLParser::ShaderSection::VERTEXSHADER);
	parser.SaveShader(glslshaderp, "testvertex.glsl");
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
	// Render
	Zorlock::Renderer2D::ResetStats();
	{
		ZL_PROFILE_SCOPE("Renderer Prep");
		Zorlock::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Zorlock::RenderCommand::Clear();
	}
	static float rotation = 0.0f;
	rotation += ts * 50.0f;

	ZL_PROFILE_SCOPE("Renderer Draw");
	Zorlock::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Zorlock::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
	Zorlock::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Zorlock::Renderer2D::EndScene();

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
