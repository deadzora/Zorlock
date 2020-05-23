#include "Sandbox2D.h"
#include <imgui/imgui.h>

using namespace Zorlock;

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor( 0.2f, 0.3f, 0.8f, 1.0f )
{
}

void Sandbox2D::OnAttach()
{
	ZL_PROFILE_FUNCTION();

	m_CheckerboardTexture = Zorlock::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	ZL_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Zorlock::Timestep ts)
{
	ZL_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Zorlock::Renderer2D::ResetStats();
	{
		ZL_PROFILE_SCOPE("Renderer Prep");
		Zorlock::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Zorlock::RenderCommand::Clear();
	}

	{
		Zorlock::Renderer2D::BeginScene(m_CameraController.GetCamera());
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		ZL_PROFILE_SCOPE("Renderer Draw");
		Zorlock::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Zorlock::Renderer2D::DrawRotatedQuad(VECTOR2( 1.0f, 0.0f ), VECTOR2( 0.8f, 0.8f ), -45.0f, COLOR4( 0.8f, 0.2f, 0.3f, 1.0f ));
		Zorlock::Renderer2D::DrawQuad(VECTOR2( -1.0f, 0.0f ), VECTOR2( 0.8f, 0.8f ), COLOR4( 0.8f, 0.2f, 0.3f, 1.0f ));
		Zorlock::Renderer2D::DrawQuad(VECTOR2( 0.5f, -0.5f ), VECTOR2( 0.5f, 0.75f ), m_SquareColor);
		Zorlock::Renderer2D::DrawQuad(VECTOR3( 0.0f, 0.0f, -0.2f ), VECTOR2( 20.0f, 20.0f ), m_CheckerboardTexture, 10.0f);
		Zorlock::Renderer2D::DrawRotatedQuad(VECTOR3( -2.0f, 0.0f, -0.005f ), VECTOR2( 1.0f, 1.0f ), rotation, m_CheckerboardTexture, 20.0f);
		Zorlock::Renderer2D::EndScene();

		
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				COLOR4 color = COLOR4( (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f , 0.7f );
				Zorlock::Renderer2D::DrawQuad(VECTOR3( x, y ,-0.15f), VECTOR2( 0.45f, 0.45f ), color);
			}
		}
		
		Zorlock::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ZL_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Zorlock::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", &m_SquareColor.x);
	ImGui::End();
}

void Sandbox2D::OnEvent(Zorlock::Event& e)
{
	m_CameraController.OnEvent(e);
}