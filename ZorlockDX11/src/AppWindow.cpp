#include "AppWindow.h"
#include "Math.h"
#include "ErrorLogger.h"
#include <string>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

AppWindow::AppWindow()
{
	//keyboard.EnableAutoRepeatChars();
}


AppWindow::~AppWindow()
{
}


void AppWindow::OnCreate()
{

	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Call CoInitialize");
	}
	GraphicsEngine::get()->Init(this->m_hwnd, this->getClientWindowRect());
	
	deviceready = true;
	
#ifndef ZORLOCKDIRECTX_EXPORTS
	
	RECT rc = this->getClientWindowRect();
	float AspectRatio = static_cast<float>((rc.right - rc.left)) / static_cast<float>((rc.bottom - rc.top));
	this->camera = GraphicsEngine::get()->CreateCamera(AspectRatio);
	this->gameobject = GraphicsEngine::get()->LoadModel(L"Data/Models/MK6_OBJ.obj"); 
	
	this->light = GraphicsEngine::get()->CreateLight(); 
	this->light->SetLightBrightness(1);
	this->light->SetLightColor(1, 0.5f, 0.5f);
	
	this->maintex = GraphicsEngine::get()->LoadTexture(L"Data/Textures/SciFi_Fighter-MK6-diffuse.jpg");
	this->gameobject->SetTexture(maintex);
	this->camera2d = GraphicsEngine::get()->CreateCamera2D(static_cast<float>((rc.right - rc.left)), static_cast<float>((rc.bottom - rc.top)));
	
	this->sprite = GraphicsEngine::get()->LoadSprite(300, 300, L"Data/Textures/me.jpg");
	sprite->SetPosition(0.0f, -0.0f, 0.0f);
	camera->SetPosition(0.0f, 0.0f, -2.0f);
#endif

}

void AppWindow::OnUpdate()
{
	while (!mouse.EventBufferIsEmpty())
	{
#ifndef ZORLOCKDIRECTX_EXPORTS
		MouseEvent me = mouse.ReadEvent();
		if (mouse.IsRightDown())
		{
			if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
			{
				this->camera->AdjustRotation((float)me.GetPosY() * 0.001f, (float)me.GetPosX() * 0.001f, 0.0f);
			}
		}
#endif
	}
	while (!keyboard.CharBufferIsEmpty())
	{

		unsigned char ch = keyboard.ReadChar();

	}
	while (!keyboard.KeyBufferIsEmpty())
	{

		unsigned char keycode = keyboard.ReadKey().GetKeyCode();

	}


#ifndef ZORLOCKDIRECTX_EXPORTS
	float cameraspeed = 0.002f;
	if (keyboard.KeyIsPressed(VK_SHIFT))
	{
		cameraspeed = 0.05f;
	}
	if (keyboard.KeyIsPressed('W'))
	{
		this->camera->AdjustPosition(this->camera->GetFowardVector()*cameraspeed);
	}
	if (keyboard.KeyIsPressed('S'))
	{
		this->camera->AdjustPosition(this->camera->GetBackVector()*cameraspeed);
	}
	if (keyboard.KeyIsPressed('A'))
	{
		this->camera->AdjustPosition(this->camera->GetLeftVector()*cameraspeed);
	}
	if (keyboard.KeyIsPressed('D'))
	{
		this->camera->AdjustPosition(this->camera->GetRightVector()*cameraspeed);
	}
	if (keyboard.KeyIsPressed('Q'))
	{
		this->camera->AdjustPosition(0.0f,cameraspeed,0.0f);
	}
	if (keyboard.KeyIsPressed('E'))
	{
		this->camera->AdjustPosition(0.0f, -cameraspeed, 0.0f);
	}
	if (keyboard.KeyIsPressed('C'))
	{
		//XMVECTOR lightPosition = this->camera->GetPositionVector();
		//lightPosition += this->camera->GetFowardVector();
		//this->light->SetPosition(lightPosition);
		//this->light->SetRotation(this->camera.GetRotationFloat3());
		
	}
	//Pre Draw
	rot += 0.0001f;
	GraphicsEngine::get()->Cls();
	gameobject->SetRotation(0, rot, 0);
	gameobject->SetPosition(0, 0, 1000);
	//GraphicsEngine::get()->setprojectionmatrix();
	sprite->SetPosition(0, 0, 0);
	//sprite->SetRotation(0, rot, 0);
#endif
	
#ifndef ZORLOCKDIRECTX_EXPORTS
	GraphicsEngine::get()->UpdateWorld();
	
	for (UINT i = 0; i < MAXNUMLIGHTS; i++)
	{
		gameobject->GetConstantLightBuffer()->setlightbright(i,1.0f);
		gameobject->GetConstantLightBuffer()->setlightattenuation(i, 1, 0.5f, 0.1f);
		gameobject->GetConstantLightBuffer()->setlightradius(i, 60000);
		
	}
	gameobject->GetConstantLightBuffer()->setlightcolor(0, 1, 0, 0);
	gameobject->GetConstantLightBuffer()->setlightcolor(1, 0, 1, 0);
	gameobject->GetConstantLightBuffer()->setlightcolor(2, 0, 0, 1);
	gameobject->GetConstantLightBuffer()->setlightcolor(3, 1, 0, 1);
	gameobject->GetConstantLightBuffer()->setlightpos(0, DirectX::XMFLOAT3(-500,0,0));
	gameobject->GetConstantLightBuffer()->setlightpos(1, DirectX::XMFLOAT3(500,0,0));
	gameobject->GetConstantLightBuffer()->setlightpos(2, DirectX::XMFLOAT3(0,500,0));
	gameobject->GetConstantLightBuffer()->setlightpos(3, DirectX::XMFLOAT3(0,-500,0));
	
#endif
	
#ifndef ZORLOCKDIRECTX_EXPORTS
	GraphicsEngine::get()->RenderWorld();
	light->UpdateLight();
	//light->Draw(this->camera->GetViewMatrix() * this->camera->GetProjectionMatrix());

	//Draw Model
	gameobject->Draw(this->camera->GetViewMatrix() * this->camera->GetProjectionMatrix());
#endif


	
#ifndef ZORLOCKDIRECTX_EXPORTS


	static int counter = 0;
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("test");
	ImGui::Text("This is example text");
	if (ImGui::Button("Click Me!"))
		counter += 1;
	ImGui::SameLine();
	std::string clickcount = "Rotation: " + std::to_string(rot);
	ImGui::Text(clickcount.c_str());
	//ImGui::DragFloat3("Translate X/Y/Z", translationOffset, 0.1f, -5.0f, 5.0f);
	//ImGui::DragFloat3("Rotate X/Y/Z", rotationOffset, 0.1f, -5.0f, 5.0f);
	//ImGui::DragFloat3("Scale X/Y/Z", scaleOffset, 0.1f, -5.0f, 5.0f);
	ImGui::End();

	ImGui::Render();
	
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	GraphicsEngine::get()->Flip();
#endif


	
	//m_swapchain->flip(false);

}



void AppWindow::OnDestroy()
{
	
	Window::OnDestroy();
	//if(this->m_vb)this->m_vb->release();
	if(this->m_ps)this->m_ps->release();
	if(this->m_vs)this->m_vs->release();
	if (this->gameobject)this->gameobject->Release();
	if(this->m_swapchain)this->m_swapchain->release();
	GraphicsEngine::get()->release();
}

#ifdef ZORLOCKDIRECTX_EXPORTS

ZORLOCKDIRECTX_API uintptr_t CreateApp()
{
	AppWindow* a = new AppWindow();
	a->init();
	uintptr_t ii = reinterpret_cast<std::uintptr_t>(a);
	return ii;
}

ZORLOCKDIRECTX_API bool AppInit(long handle)
{
	AppWindow* a = (AppWindow*)&handle;
	return a->init();
}

ZORLOCKDIRECTX_API bool AppRunning(long handle)
{
	AppWindow* a = (AppWindow*)&handle;
	return a->isRunning();
}

ZORLOCKDIRECTX_API bool AppBroadCast(long handle)
{
	AppWindow* a = (AppWindow*)&handle;
	return a->broadcast();
}

ZORLOCKDIRECTX_API bool GraphicsReady(long handle)
{
	AppWindow* a = (AppWindow*)&handle;
	return a->deviceready;
}

ZORLOCKDIRECTX_API void GraphicsCLS()
{
	GraphicsEngine::get()->Cls();
}

ZORLOCKDIRECTX_API void GraphicsUpdate()
{
	GraphicsEngine::get()->UpdateWorld();
}

ZORLOCKDIRECTX_API void GraphicsRender()
{
	GraphicsEngine::get()->RenderWorld();
}

ZORLOCKDIRECTX_API void GraphicsFlip()
{
	GraphicsEngine::get()->Flip();
}

ZORLOCKDIRECTX_API long CreateCamera(long handle)
{
	AppWindow* a = (AppWindow*)&handle;
	RECT rc = a->getClientWindowRect();
	float AspectRatio = static_cast<float>((rc.right - rc.left)) / static_cast<float>((rc.bottom - rc.top));
	Camera* c = a->camera = GraphicsEngine::get()->CreateCamera(AspectRatio);
	uintptr_t ii = reinterpret_cast<std::uintptr_t>(c);
	return ii;

}

ZORLOCKDIRECTX_API long CreateOrthoCamera(long handle)
{
	AppWindow* a = (AppWindow*)&handle;
	RECT rc = a->getClientWindowRect();
	OrthoCamera* o = a->camera2d = GraphicsEngine::get()->CreateCamera2D(static_cast<float>((rc.right - rc.left)), static_cast<float>((rc.bottom - rc.top)));
	uintptr_t ii = reinterpret_cast<std::uintptr_t>(o);
	return ii;
}

ZORLOCKDIRECTX_API long LoadSprite(std::string file, int w, int h)
{
	wchar_t* wide_string = new wchar_t[file.length() + 1];
	std::copy(file.begin(), file.end(), wide_string);
	wide_string[file.length()] = 0;
	Sprite* s = GraphicsEngine::get()->LoadSprite(w, h, wide_string);
	delete[] wide_string;
	uintptr_t ii = reinterpret_cast<std::uintptr_t>(s);
	return ii;
}

ZORLOCKDIRECTX_API void SetSpritePosition(long sprite, int x, int y)
{
	Sprite* s = (Sprite*)&sprite;
	s->SetPosition(x, y, 0);
}


#endif



