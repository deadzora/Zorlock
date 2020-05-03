#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "ConstantPixelBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "RenderableObject.h"
//#include "voxel/marching.h"
//#include <plog/Log.h>

class EditorWindow : public Window
{
public:
	EditorWindow();
	~EditorWindow();
	void OnUpdate() override;
	void OnCreate() override;
	void OnDestroy() override;
	void InitGUI();
	void DrawGUI();
	void UpdateGUI();
	void UpdateCamera();
	Camera * camera;
private:
	void EditorTabs();
	void ProjectTab();
	void MediaTab();

};

