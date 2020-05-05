#pragma once
#include "ZLpch.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <string>
#include <combaseapi.h>

namespace ZorlockDX11
{


	typedef bool (*DX11ContextCallback)(int);
	typedef void (*DX11ErrorCallback)(int, const char*);


	class DirectX11Window
	{
	public:
		DirectX11Window();
		bool init();
		bool init(int w, int h, std::string title);
		bool release();
		bool DX11PollEvents();
		bool isRunning();
		HWND windowhandle();
		RECT getClientWindowRect();
		void SetContextCallback(DX11ContextCallback f);
		void SetErrorCallback(DX11ErrorCallback f);
		void SetHWND(HWND hwnd);
		void OnUpdate();
		void OnCreate();
		void OnDestroy();


		Keyboard keyboard;
		Mouse mouse;
		LPCWSTR WindowName = L"DXAPP";
		void* userPointer;
		~DirectX11Window();
	private:
		DX11ContextCallback contextcallback;
		DX11ErrorCallback errorcallback;
	protected:
		HWND m_hwnd;
		bool m_is_running;
	
	};

	void* DX11GetWindowUserPointer(DirectX11Window* window);
	void DX11SetWindowUserPointer(DirectX11Window* handle, void* pointer);

	//Set event callbacks here
	typedef void (*DX11MouseButtonFunc)(DirectX11Window*,int,int,int);
	typedef void (*DX11CharFunc)(DirectX11Window*, unsigned int);
	typedef void (*DX11KeyFunc)(DirectX11Window*, int, int, int, int);
	typedef void (*DX11CloseFunc)(DirectX11Window*);
	typedef void (*DX11WindowSizeFunc)(DirectX11Window*, int, int);
	typedef void (*DX11ScrollFunc)(DirectX11Window*, double, double);
	typedef void (*DX11MousePosFunc)(DirectX11Window*, double, double);


	void DX11SetMouseButtonCallback(DX11MouseButtonFunc func);
	void DX11SetCharacterCallback(DX11CharFunc func);
	void DX11SetKeyCallback(DX11KeyFunc func);
	void DX11SetCloseCallback(DX11CloseFunc func);
	void DX11SetWindowSizeCallback(DX11WindowSizeFunc func);
	void DX11SetScrollCallback(DX11ScrollFunc func);
	void DX11SetMousePosCallback(DX11MousePosFunc func);


	enum DX_KEYACTION {
		DX_RELEASE = 0,
		DX_PRESS = 1,
		DX_REPEATE = 2
	};

}