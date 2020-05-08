#pragma once

#include <Windows.h>
#include <string>
#include "Keyboard.h"
#include "Mouse.h"
#include "Zorlock/Core/Window.h"

#define ZWINDOW(x) static_cast<DX11Raz::ZWindow*>(x);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

namespace DX11Raz
{



	typedef void(*Win32ErrorCallBack)(int, const char*);

	struct ZWindowData;
	//typedefs for callbacks

	enum DX_KEYACTION {
		DX_RELEASE = 0,
		DX_PRESS = 1,
		DX_REPEATE = 2
	};

	class ZWin
	{

	};

	typedef void (*WindowSizeCallback)(DX11Raz::ZWin*, int, int);
	typedef void (*WindowCloseCallback)(DX11Raz::ZWin*);
	typedef void (*WindowKeyCallback)(DX11Raz::ZWin*, int, int, int, int);
	typedef void (*WindowMouseButtonCallback)(DX11Raz::ZWin*, int, int, int);
	typedef void (*WindowCharCallback)(DX11Raz::ZWin*, unsigned int);
	typedef void (*WindowScrollCallback)(DX11Raz::ZWin*, double, double);
	typedef void (*WindowMousePosCallback)(DX11Raz::ZWin*, double, double);


	class DX11DeviceContext;

	class ZWindow : public ZWin
	{
	public:
		ZWindow();
		bool init(UINT w, UINT h, LPCWSTR windowname);
		bool release();
		bool PollEvents();
		bool isRunning();

		RECT getClientWindowRect();
		void SetHWND(HWND hwnd);
		HWND GetHWND();
		UINT GetWidth();
		UINT GetHeight();
		LRESULT ZWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		virtual void OnUpdate();
		virtual void OnCreate();
		virtual void OnDestroy();
		DX11DeviceContext* GetDeviceContext();
		void SetDeviceContext(DX11DeviceContext* context);
		Keyboard keyboard;
		Mouse mouse;
		LPCWSTR WindowName = L"DXAPP";
		~ZWindow();		
		void* data;
		WindowMouseButtonCallback WMBCallback;
		WindowCloseCallback WCCallback;
		WindowKeyCallback WKCallback;
		WindowSizeCallback WSCallback;
		WindowCharCallback WCharCallback;
		WindowScrollCallback WScrollCallback;
		WindowMousePosCallback WMPCallback;
	private:
		//we want to keep a copy of the devicecontext on the window
		DX11DeviceContext * device_context;
		
	protected:
		HWND m_hwnd;
		bool m_is_running;
		UINT width;
		UINT height;

	};




	ZWindow* ZCreateWindow(UINT w, UINT h, LPCWSTR windowname);
	void SetWindowUserPointer(ZWindow * window, void * data);
	void * GetWindowUserPointer(ZWindow * window);
	void SetZWindowCallback(Win32ErrorCallBack f);
	int InitZWindows();
	void ZDestroyWindow(ZWindow * m_Window);
	void ZTerminate();

	void ZSetMouseButtonCallback(ZWindow * win, WindowMouseButtonCallback func);
	void ZSetCharacterCallback(ZWindow* win, WindowCharCallback func);
	void ZSetKeyCallback(ZWindow* win, WindowKeyCallback func);
	void ZSetCloseCallback(ZWindow* win, WindowCloseCallback func);
	void ZSetWindowSizeCallback(ZWindow* win, WindowSizeCallback func);
	void ZSetScrollCallback(ZWindow* win, WindowScrollCallback func);
	void ZSetMousePosCallback(ZWindow* win, WindowMousePosCallback func);

}
