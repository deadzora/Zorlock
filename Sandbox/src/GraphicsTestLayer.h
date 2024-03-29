#pragma once

#include "Zorlock.h"

class GraphicsTestLayer : public Zorlock::Layer
{
public:
	GraphicsTestLayer();
	virtual ~GraphicsTestLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Zorlock::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Zorlock::Event& e) override;

private:

	Zorlock::Ref<Zorlock::Shader> m_Shader;
	Zorlock::Ref<Zorlock::VertexArray> m_VertexArray;

	Zorlock::Ref<Zorlock::Shader> m_FlatColorShader;
	Zorlock::Ref<Zorlock::VertexArray> m_SquareVA;

	Zorlock::Ref<Zorlock::Texture2D> m_Texture, m_ChernoLogoTexture;

	Zorlock::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};