#pragma once

#include "Zorlock.h"

class ZorlockEditor : public Zorlock::Layer
{
public:
	ZorlockEditor();
	~ZorlockEditor() {};
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(ZLTIME ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(ZLEVENT& e) override;



protected:
	bool appready;
	float FOV = 90.0f;
	float AspectRatio = 1280.0f / 720.0f;
	float nearZ = 0.01f;
	float farZ = 3000.0f;
	ZLREF<ZLSCENE> m_mainScene;
	ZLREF<ZLCAMERA> mainCam;
	Zorlock::OrthographicCameraController m_CameraController;
};