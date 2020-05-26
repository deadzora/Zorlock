#pragma once

#include "Zorlock.h"
#include "Zorlock/Components/MeshRenderer.h"

class SceneLayer : public Zorlock::Layer
{
public:
	SceneLayer();
	virtual ~SceneLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(ZLTIME ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(ZLEVENT& e) override;
private:
	float FOV = 90.0f;
	float AspectRatio = 1280.0f / 720.0f;
	float nearZ = 0.01f;
	float farZ = 3000.0f;
	ZLREF<ZLSCENE> m_mainScene;
	ZLREF<ZLGAMEOBJECT> mainmodel;
	ZLREF<ZLTEXTURE2D> m_Texture;
	ZLREF<ZLCAMERA> mainCam;

	ZLREF<ZLSHADER> m_Shader;
	ZLREF<ZLVARRAY> m_VertexArray;
	ZLREF<ZLSHADER> m_FlatColorShader;
	ZLREF<ZLVARRAY> m_SquareVA;
	ZLREF<ZLSHADER> textureShader;
	ZLREF<ZLTEXTURE2D> m_ChernoLogoTexture;
	ZLREF<Zorlock::MeshRenderer> m_meshrenderer;
	Zorlock::COLOR m_SquareColor = { 0.2f, 0.3f, 0.8f };

};