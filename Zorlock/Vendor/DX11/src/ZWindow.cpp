#include "ZLpch.h"
#include "ZWindow.h"
#include <windowsx.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include "DX11DeviceContext.h"

namespace DX11Raz
{





	Win32ErrorCallBack Errorcallback = nullptr;

	ZWindow::ZWindow()
	{
		
		static bool raw_input_initialized = false;
		/*
		if (raw_input_initialized == false)
		{
			RAWINPUTDEVICE rid;

			rid.usUsagePage = 0x01;
			rid.usUsage = 0x02;
			rid.dwFlags = 0;
			rid.hwndTarget = 0;

			if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
			{
				//ErrorLogger::Log(GetLastError(), "Failed to register raw input devices.");
				exit(-1);
			}
			raw_input_initialized = true;
		}
		*/
	}


	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{ 
		if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
			return true;

		ZWindow* pThis;
		if (msg == WM_NCCREATE)
		{
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lparam);
			pThis = static_cast<ZWindow*>(lpcs->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA,
				reinterpret_cast<LONG_PTR>(pThis));

		}
		else {
			pThis = reinterpret_cast<ZWindow*>(
				GetWindowLongPtr(hwnd, GWLP_USERDATA));
		}

		if (pThis)
		{
			return pThis->ZWndProc(hwnd, msg, wparam, lparam);
		}

		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	bool ZWindow::init(UINT w, UINT h, LPCWSTR windowname)
	{
		width = w;
		height = h;
		this->WindowName = windowname;
		WNDCLASSEX wc;
		wc.cbClsExtra = NULL;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.cbWndExtra = NULL;
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wc.hInstance = NULL;
		wc.lpszClassName = L"MyWindowClass";
		wc.lpszMenuName = L"";
		wc.style = NULL;
		wc.lpfnWndProc = &WndProc;
		if (!::RegisterClassEx(&wc))
			return false;

		/*
		if (!window)
			window = this;
			*/
		m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", this->WindowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, w, h,
			NULL, NULL, NULL, this);
		if (!m_hwnd)
		{
			Errorcallback(1,"Could Not Create a Raz Window!");
			return false;
		}
		ShowWindow(m_hwnd, SW_SHOW);
		UpdateWindow(m_hwnd);


		m_is_running = true;

		return true;
	}

	bool ZWindow::release()
	{
		//be sure to release the graphics!
		device_context->Release();
		if (!::DestroyWindow(m_hwnd))
			return false;

		return true;
	}

	bool ZWindow::PollEvents()
	{
		MSG msg;
		this->OnUpdate();
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)>0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	
		Sleep(0);
		return true;
	}

	bool ZWindow::isRunning()
	{
		return m_is_running;
	}

	RECT ZWindow::getClientWindowRect()
	{
		RECT rc;
		::GetClientRect(this->m_hwnd, &rc);
		return rc;
	}

	void ZWindow::SetHWND(HWND hwnd)
	{
		this->m_hwnd = hwnd;
	}

	HWND ZWindow::GetHWND()
	{
		return m_hwnd;
	}

	UINT ZWindow::GetWidth()
	{
		return width;
	}

	UINT ZWindow::GetHeight()
	{
		return height;
	}

	LRESULT ZWindow::ZWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{

		switch (msg)
		{


		case WM_MOUSEMOVE:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			this->mouse.OnMouseMove(x, y);
			this->WMPCallback(this, x, y);

			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			this->mouse.OnLeftPressed(x, y);
			this->WMBCallback(this, msg, 0, 0);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			this->mouse.OnRightPressed(x, y);
			this->WMBCallback(this, msg, 0, 0);
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			this->mouse.OnMiddlePressed(x, y);
			this->WMBCallback(this, msg, 0, 0);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			this->mouse.OnLeftReleased(x, y);
			this->WMBCallback(this, msg, 0, 0);
			return 0;
		}
		case WM_RBUTTONUP:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			this->mouse.OnRightReleased(x, y);
			this->WMBCallback(this, msg, 0, 0);
			return 0;
		}
		case WM_MBUTTONUP:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			this->mouse.OnMiddleReleased(x, y);
			this->WMBCallback(this, msg, 0, 0);
			return 0;
		}

		case WM_MOUSEWHEEL:
		{
			double x = (double)GET_X_LPARAM(lparam)/ (double)WHEEL_DELTA;
			double y = (double)GET_Y_LPARAM(lparam) / (double)WHEEL_DELTA;
			if (GET_WHEEL_DELTA_WPARAM(wparam) > 0)
			{
				this->WScrollCallback(this, (int)x, y);
				this->mouse.OnWheelUp((int)x, GET_WHEEL_DELTA_WPARAM(wparam));
			}
			else if (GET_WHEEL_DELTA_WPARAM(wparam) < 0)
			{
				this->WScrollCallback(this, (int)x, -y);
				this->mouse.OnWheelDown((int)x, GET_WHEEL_DELTA_WPARAM(wparam));
			}
			break;
		}
		/*
		case WM_INPUT:
		{
			UINT dataSize;

			GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

			if (dataSize > 0)
			{
				std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
				if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
				{
					RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
					if (raw->header.dwType == RIM_TYPEMOUSE)
					{
						this->mouse.OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
					}
				}
			}

			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}
		*/
		case WM_KEYDOWN:
		{
			unsigned char keycode = static_cast<unsigned char>(wparam);
			if (keyboard.KeyIsPressed(keycode))
			{
				this->keyboard.EnableAutoRepeatKeys();
			}
			if (this->keyboard.IsKeysAutoRepeat())
			{
				this->WKCallback(this, keycode, keycode, DX_KEYACTION::DX_REPEATE, 0);
				this->keyboard.OnKeyPressed(keycode);
			}
			else
			{
				const bool wasPressed = lparam & 0x40000000;
				if (!wasPressed)
				{
					this->WKCallback(this, keycode, keycode, DX_KEYACTION::DX_PRESS, 0);
					this->keyboard.OnKeyPressed(keycode);
				}
			}

			return 0;
		}

		case WM_KEYUP:
		{
			unsigned char keycode = static_cast<unsigned char>(wparam);
			this->keyboard.OnKeyReleased(keycode);
			this->keyboard.DisableAutoRepeatKeys();
			this->keyboard.DisableAutoRepeatChars();
			this->WKCallback(this, keycode, keycode, DX_KEYACTION::DX_RELEASE, 0);
			return 0;
		}

		case WM_CHAR:
		{
			unsigned char ch = static_cast<unsigned char>(wparam);
			if (this->keyboard.KeyIsPressed(ch))
			{
				this->keyboard.EnableAutoRepeatChars();
			}
			if (this->keyboard.IsCharsAutoRepeat())
			{	
				this->WCharCallback(this, ch);
				this->keyboard.OnChar(ch);
			}
			else
			{
				const bool wasPressed = lparam & 0x40000000;
				if (!wasPressed)
				{
					this->WCharCallback(this, ch);
					this->keyboard.OnChar(ch);
				}
			}
			return 0;
			break;
		}
		case WM_CREATE:
		{
			this->SetHWND(hwnd);
			this->OnCreate();
			break;
		}
		case WM_DESTROY:
		{
			this->WCCallback(this);
			this->OnDestroy();
			::PostQuitMessage(0);
			break;
		}
		case WM_SIZING:
		{
			RECT rc = this->getClientWindowRect();
			int w = static_cast<int>((rc.right - rc.left));
			int h = static_cast<int>((rc.bottom - rc.top));

			WSCallback(this, w, h);
			return 0;
			break;
		}
		default:
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}

		return NULL;

	}

	void ZWindow::OnUpdate()
	{


	}


	void ZWindow::OnCreate()
	{
	}

	void ZWindow::OnDestroy()
	{
		m_is_running = false;
	}

	DX11DeviceContext* ZWindow::GetDeviceContext()
	{
		return device_context;
	}

	void ZWindow::SetDeviceContext(DX11DeviceContext* context)
	{
		device_context = context;
	}

	ZWindow::~ZWindow()
	{
	}

	void SetZWindowCallback(Win32ErrorCallBack f)
	{
		Errorcallback = f;
	}

	ZWindow* ZCreateWindow(UINT w, UINT h, LPCWSTR windowname)
	{
		ZWindow* win = new ZWindow();
		win->init(w, h, windowname);
		return win;
	}

	void SetWindowUserPointer(ZWindow* window, void* data)
	{
		window->data = data;
	}

	void* GetWindowUserPointer(ZWindow* window)
	{
		return window->data;
	}


	int InitZWindows()
	{
		//i mean i guess there's some kind of init i can do pre creation of windows

		return 1;
	}
	void ZDestroyWindow(ZWindow* m_Window)
	{
		m_Window->release();
		
	}

	void ZTerminate()
	{
		return;
	}

	void ZSetMouseButtonCallback(ZWindow* win, WindowMouseButtonCallback func)
	{
		win->WMBCallback = func;
	}
	void ZSetCharacterCallback(ZWindow* win, WindowCharCallback func)
	{
		win->WCharCallback = func;
	}
	void ZSetKeyCallback(ZWindow* win, WindowKeyCallback func)
	{
		win->WKCallback = func;
	}
	void ZSetCloseCallback(ZWindow* win, WindowCloseCallback func)
	{
		win->WCCallback = func;
	}
	void ZSetWindowSizeCallback(ZWindow* win, WindowSizeCallback func)
	{
		win->WSCallback = func;
	}
	void ZSetScrollCallback(ZWindow* win, WindowScrollCallback func)
	{
		win->WScrollCallback = func;
	}
	void ZSetMousePosCallback(ZWindow* win, WindowMousePosCallback func)
	{
		win->WMPCallback = func;
	}
}