#pragma once

#include <Zorlock.h>


class DX11Layer : public Zorlock::Layer
{
public:
	DX11Layer();
	virtual ~DX11Layer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Zorlock::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Zorlock::Event& e) override;

private:
	float rotation;
	Zorlock::Ref<Zorlock::Shader> m_Shader;
	Zorlock::Ref<Zorlock::VertexArray> m_VertexArray;

	Zorlock::Ref<Zorlock::Shader> m_FlatColorShader;
	Zorlock::Ref<Zorlock::VertexArray> m_SquareVA;

	Zorlock::Ref<Zorlock::Texture2D> m_Texture, m_ChernoLogoTexture;

	Zorlock::OrthographicCameraController m_CameraController;
	COLOR m_SquareColor = { 1.0, 0.8f, 0.9f };
};