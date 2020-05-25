#pragma once

#include "Zorlock.h"
using namespace Zorlock;

class ExampleLayer : public ZLLAYER
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Zorlock::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Zorlock::Event& e) override;
private:	
	ZLREF<ZLSHADER> m_Shader;
	ZLREF<ZLVARRAY> m_VertexArray;
	ZLREF<ZLSHADER> m_FlatColorShader;
	ZLREF<ZLVARRAY> m_SquareVA;
	ZLREF<ZLSHADER> textureShader;
	ZLREF<ZLTEXTURE2D> m_Texture, m_ChernoLogoTexture;
	ZLCAMERACONTROLLER(ZLORTHO) m_CameraController;
	COLOR m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

