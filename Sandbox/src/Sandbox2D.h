#pragma once

#include "Zorlock.h"

class Sandbox2D : public Zorlock::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Zorlock::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Zorlock::Event& e) override;
private:
	Zorlock::OrthographicCameraController m_CameraController;
	
	// Temp
	Zorlock::Ref<Zorlock::VertexArray> m_SquareVA;
	Zorlock::Ref<Zorlock::Shader> m_FlatColorShader;

	Zorlock::Ref<Zorlock::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};