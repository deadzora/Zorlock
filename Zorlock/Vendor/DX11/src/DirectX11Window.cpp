#include "ZLpch.h"
#include "DirectX11Window.h"
#include "DX11Graphics.h"
#include <windowsx.h>


namespace ZorlockDX11
{



	DirectX11Window* window = nullptr;
	DX11MouseButtonFunc mouseCallback = nullptr;
	DX11CharFunc charCallback = nullptr;
	DX11KeyFunc keyCallback = nullptr;
	DX11CloseFunc closeCallback = nullptr;
	DX11WindowSizeFunc windowsizeCallback = nullptr;
	DX11ScrollFunc scrollCallback = nullptr;
	DX11MousePosFunc mouseposCallback = nullptr;

	int DisplayResourceNAMessageBox()
	{
		RAWINPUTDEVICE rid;

		rid.usUsagePage = 0x01;
		rid.usUsage = 0x02;
		rid.dwFlags = 0;
		rid.hwndTarget = 0;

		int msgboxID = MessageBox(
			NULL,
			(LPCWSTR)L"Raw Input Device not available\nHow are you using a PC???",
			(LPCWSTR)L"Zorlock DirectX11",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);

		switch (msgboxID)
		{
		case IDCANCEL:

			break;
		case IDTRYAGAIN:
			if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
			{
				DisplayResourceNAMessageBox();
			}
			break;
		case IDCONTINUE:
			// TODO: add code
			break;
		}

		return msgboxID;
	}

	DirectX11Window::DirectX11Window() : contextcallback(NULL), m_hwnd(NULL), m_is_running(false), errorcallback(NULL)
	{
		static bool raw_input_initialized = false;
		if (raw_input_initialized == false)
		{
			RAWINPUTDEVICE rid;

			rid.usUsagePage = 0x01;
			rid.usUsage = 0x02;
			rid.dwFlags = 0;
			rid.hwndTarget = 0;

			if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
			{

				if (DisplayResourceNAMessageBox() != 11)
				{
					exit(-1);
				}
				else {
					raw_input_initialized = false;
				}
			}
			else {
				raw_input_initialized = true;
			}
			
		}

	}

	//extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{ 
		//if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		//	return true;

		switch (msg)
		{

		case WM_MOUSEMOVE:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			window->mouse.OnMouseMove(x, y);
			mouseposCallback(window, x, y);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			window->mouse.OnLeftPressed(x, y);
			mouseCallback(window, WM_LBUTTONDOWN,x, y);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			window->mouse.OnRightPressed(x, y);
			mouseCallback(window, WM_RBUTTONDOWN, x, y);
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			window->mouse.OnMiddlePressed(x, y);
			mouseCallback(window, WM_MBUTTONDOWN, x, y);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			window->mouse.OnLeftReleased(x, y);
			mouseCallback(window, WM_LBUTTONUP, x, y);
			return 0;
		}
		case WM_RBUTTONUP:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			window->mouse.OnRightReleased(x, y);
			mouseCallback(window, WM_RBUTTONUP, x, y);
			return 0;
		}
		case WM_MBUTTONUP:
		{
			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);
			window->mouse.OnMiddleReleased(x, y);
			mouseCallback(window, WM_MBUTTONUP, x, y);
			return 0;
		}

		case WM_MOUSEWHEEL:
		{
			double x = GET_X_LPARAM(lparam);
			double y = GET_Y_LPARAM(lparam);
			if (GET_WHEEL_DELTA_WPARAM(wparam) > 0)
			{
				window->mouse.OnWheelUp(x, y);
				scrollCallback(window, x, y);
			}
			else if (GET_WHEEL_DELTA_WPARAM(wparam) < 0)
			{
				window->mouse.OnWheelDown(x, y);
				scrollCallback(window, x, y);
			}
			break;
		}

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
						window->mouse.OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
					}
				}
			}
		
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}

		case WM_KEYDOWN:
		{
			unsigned char keycode = static_cast<unsigned char>(wparam);
			if (window->keyboard.IsKeysAutoRepeat())
			{
				window->keyboard.OnKeyPressed(keycode);
				keyCallback(window, keycode, keycode, DX_KEYACTION::DX_PRESS, 0);
			}
			else 
			{
				const bool wasPressed = lparam & 0x40000000;
				if (!wasPressed)
				{
					keyCallback(window, keycode, keycode, DX_KEYACTION::DX_REPEATE, 0);
					window->keyboard.OnKeyPressed(keycode);
				}
			}
		
			return 0;
		}

		case WM_KEYUP:
		{
			unsigned char keycode = static_cast<unsigned char>(wparam);
			window->keyboard.OnKeyReleased(keycode);
			keyCallback(window, keycode, keycode, DX_KEYACTION::DX_RELEASE, 0);
			return 0;
		}

		case WM_CHAR:
		{
			unsigned char ch = static_cast<unsigned char>(wparam);
			if (window->keyboard.IsCharsAutoRepeat())
			{
				charCallback(window, ch);
				window->keyboard.OnChar(ch);
			}
			else
			{
				const bool wasPressed = lparam & 0x40000000;
				if (!wasPressed)
				{
					charCallback(window, ch);
					window->keyboard.OnChar(ch);
				}
			}
			return 0;
			break;
		}
		case WM_CREATE:
		{
			window->SetHWND(hwnd);
			window->OnCreate();
			break;
		}
		case WM_DESTROY:
		{
			window->OnDestroy();
			::PostQuitMessage(0);
			exit(0);
			break;
		}
		case WM_SIZING:
		{
			RECT rc = window->getClientWindowRect();
			int w = static_cast<int>((rc.right - rc.left));
			int h = static_cast<int>((rc.bottom - rc.top));
			windowsizeCallback(window, w, h);
			return 0;
			break;
		}
		default:
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}

		return NULL;
	}

	bool DirectX11Window::init()
	{
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

		if (!window)
			window = this;

		m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", this->WindowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
			NULL, NULL, NULL, NULL);
		if (!m_hwnd)
			return false;

		::ShowWindow(m_hwnd, SW_SHOW);
		::UpdateWindow(m_hwnd);


		m_is_running = true;

		return true;
	}

	bool DirectX11Window::init(int w, int h, std::string title)
	{
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

		if (!window)
			window = this;
		LPCWSTR lpcwName = std::wstring(title.begin(), title.end()).c_str();
		m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", lpcwName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, w, h,
			NULL, NULL, NULL, NULL);
		if (!m_hwnd)
			return false;

		::ShowWindow(m_hwnd, SW_SHOW);
		::UpdateWindow(m_hwnd);


		m_is_running = true;

		return true;
	}

	bool DirectX11Window::release()
	{
		if (!::DestroyWindow(m_hwnd))
			return false;

		return true;
	}

	bool DirectX11Window::DX11PollEvents()
	{
		MSG msg;
		//window->OnUpdate();
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)>0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	
		Sleep(0);
		return true;
	}

	bool DirectX11Window::isRunning()
	{
		return m_is_running;
	}

	HWND DirectX11Window::windowhandle()
	{
		return m_hwnd;
	}

	RECT DirectX11Window::getClientWindowRect()
	{
		RECT rc;
		::GetClientRect(this->m_hwnd, &rc);
		return rc;
	}

	void DirectX11Window::SetContextCallback(DX11ContextCallback f)
	{
		
		contextcallback = f;
	}

	void DirectX11Window::SetErrorCallback(DX11ErrorCallback f)
	{
		this->errorcallback = f;
	}

	void DirectX11Window::SetHWND(HWND hwnd)
	{
		this->m_hwnd = hwnd;
	}

	void DirectX11Window::OnUpdate()
	{
	}


	void DirectX11Window::OnCreate()
	{
		HRESULT hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			ZL_CORE_ASSERT(0, "Failed to initialize Glad!");
			return;
		}

		DX11GraphicsEngine::get()->Init(m_hwnd, getClientWindowRect());
		ZL_CORE_INFO("DX11 Info:");
		ZL_CORE_INFO(" Vendor: Zorlock DX11 Engine");
		ZL_CORE_INFO(" Vendor: Written by: Landon Ritchie");
		return;

		//this->contextcallback(1);
	}

	void DirectX11Window::OnDestroy()
	{
		m_is_running = false;
	}

	DirectX11Window::~DirectX11Window()
	{
	}




	void* DX11GetWindowUserPointer(DirectX11Window* handle)
	{
		DirectX11Window* xwindow = (DirectX11Window*)handle;
		assert(xwindow != NULL);
		return xwindow->userPointer;
	}

	void DX11SetWindowUserPointer(DirectX11Window* handle, void* pointer)
	{
		DirectX11Window* xwindow = (DirectX11Window*)handle;
		assert(xwindow != NULL);
		xwindow->userPointer = pointer;
	}

	void DX11SetMouseButtonCallback(DX11MouseButtonFunc func)
	{
		mouseCallback = func;
	}

	void DX11SetCharacterCallback(DX11CharFunc func)
	{
		charCallback = func;
	}

	void DX11SetKeyCallback(DX11KeyFunc func)
	{
		keyCallback = func;
	}

	void DX11SetCloseCallback(DX11CloseFunc func)
	{
		closeCallback = func;
	}

	void DX11SetWindowSizeCallback(DX11WindowSizeFunc func)
	{
		windowsizeCallback = func;
	}

	void DX11SetScrollCallback(DX11ScrollFunc func)
	{
		scrollCallback = func;
	}

	void DX11SetMousePosCallback(DX11MousePosFunc func)
	{
		mouseposCallback = func;
	}



}
