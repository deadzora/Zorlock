#pragma once
#include "ZLpch.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <string>
#include <combaseapi.h>

namespace ZorlockDX11
{


typedef bool (*DX11ContextCallback)(int);
	
class DirectX11Window
{
public:
	DirectX11Window();
	bool init();
	bool init(int w, int h, std::string title);
	bool release();
	bool broadcast();
	bool isRunning();
	HWND windowhandle();
	RECT getClientWindowRect();
	void SetContextCallback(DX11ContextCallback f);
	void SetHWND(HWND hwnd);
	void OnUpdate();
	void OnCreate();
	void OnDestroy();
	Keyboard keyboard;
	Mouse mouse;
	LPCWSTR WindowName = L"DXAPP";
	~DirectX11Window();
private:
	DX11ContextCallback contextcallback;
protected:
	HWND m_hwnd;
	bool m_is_running;
	
};


}