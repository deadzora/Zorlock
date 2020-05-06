#pragma once

#include <Windows.h>
#include <string>
#include "Keyboard.h"
#include "Mouse.h"
#include "Zorlock/Core/Window.h"

namespace DX11Raz
{

	typedef void(*Win32ErrorCallBack)(int, const char*);



	class ZWindow
	{
	public:
		ZWindow();
		bool init(UINT w, UINT h, LPCWSTR windowname);
		bool release();
		bool broadcast();
		bool isRunning();

		RECT getClientWindowRect();
		void SetHWND(HWND hwnd);
		LRESULT ZWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		virtual void OnUpdate();
		virtual void OnCreate();
		virtual void OnDestroy();
		
		Keyboard keyboard;
		Mouse mouse;
		LPCWSTR WindowName = L"DXAPP";
		~ZWindow();
		void SetProps(Zorlock::WindowProps* props);
	private:
		Zorlock::WindowProps* winprops;
	protected:
		HWND m_hwnd;
		bool m_is_running;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			//EventCallbackFn EventCallback;
		};

	};
	static ZWindow* ZCreateWindow(UINT w, UINT h, LPCWSTR windowname);
	//static void SetWindowUserPointer(ZWindow * s,  props);
	static void SetZWindowCallback(Win32ErrorCallBack f);
	static int InitZWindows();
}