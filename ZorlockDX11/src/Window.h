#pragma once
#include "ZLpch.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <string>

class Window
{
public:
	Window();
	bool init();
	bool release();
	bool broadcast();
	bool isRunning();
	HWND windowhandle();
	RECT getClientWindowRect();
	void SetHWND(HWND hwnd);
	virtual void OnUpdate()=0;
	virtual void OnCreate()=0;
	virtual void OnDestroy();
	Keyboard keyboard;
	Mouse mouse;
	LPCWSTR WindowName = L"DXAPP";
	~Window();
private:
	
protected:
	HWND m_hwnd;
	bool m_is_running;
	
};

