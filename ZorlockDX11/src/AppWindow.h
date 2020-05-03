#pragma once

#ifdef ZL_BUILD_DLL
#define ZORLOCKDIRECTX_API __declspec(dllexport)
#else
#ifdef ZORLOCKIMPORTS
#define ZORLOCKDIRECTX_API __declspec(dllimport)
#endif
#endif
#include <stdint.h>
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Camera.h"
#include "OrthoCamera.h"
#include "Model.h"
#include "Sprite.h"
#include "Light.h"
#include "RenderableObject.h"


#ifdef ZL_BUILD_DLL

extern "C" ZORLOCKDIRECTX_API uintptr_t CreateApp();

extern "C" ZORLOCKDIRECTX_API bool AppInit(long handle);

extern "C" ZORLOCKDIRECTX_API bool AppRunning(long handle);

extern "C" ZORLOCKDIRECTX_API bool AppBroadCast(long handle);

extern "C" ZORLOCKDIRECTX_API bool GraphicsReady(long handle);

extern "C" ZORLOCKDIRECTX_API void GraphicsCLS();

extern "C" ZORLOCKDIRECTX_API void GraphicsUpdate();

extern "C" ZORLOCKDIRECTX_API void GraphicsRender();

extern "C" ZORLOCKDIRECTX_API void GraphicsFlip();

extern "C" ZORLOCKDIRECTX_API long CreateCamera(long handle);

extern "C" ZORLOCKDIRECTX_API long CreateOrthoCamera(long handle);

extern "C" ZORLOCKDIRECTX_API long LoadSprite(std::string file, int w, int h);

extern "C" ZORLOCKDIRECTX_API void SetSpritePosition(long sprite, int x, int y);

#endif




class AppWindow: public Window
{
public:
	AppWindow();
	~AppWindow();
	float rot;
	// Inherited via Window
	virtual void OnUpdate() override;
	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	bool deviceready;
	Camera * camera;
	OrthoCamera * camera2d;
	Sprite* sprite;
private:
	SwapChain* m_swapchain;
	//VertexBuffer* m_vb;
	//IndexBuffer* m_ib;
	ConstantBuffer<CB_VS_VertexShader3>* m_cb;
	ConstantBuffer<CB_PS_PixelShader>* m_pcb;
	ConstantBuffer<CB_PS_LIGHTS>* l_pcb;
	ConstantBuffer<CB_PS_AmbientShader>* a_pcb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	//MarchingCubes m_mc;
	RenderableObject* gameobject;
	Light * light;
	//demo vars
	Texture * maintex;
	ID3D11ShaderResourceView* texture;
	ID3D11ShaderResourceView* textureB;
};

