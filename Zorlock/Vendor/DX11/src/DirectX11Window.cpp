#include "DirectX11Window.h"



namespace ZorlockDX11
{
	DirectX11Window* window = nullptr;

	DirectX11Window::DirectX11Window() : contextcallback(NULL), m_hwnd(NULL), m_is_running(false)
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
				//ErrorLogger::Log(GetLastError(), "Failed to register raw input devices.");
				exit(-1);
			}
			raw_input_initialized = true;
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
			int x = LOWORD(lparam);
			int y = HIWORD(lparam);
			window->mouse.OnMouseMove(x, y);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lparam);
			int y = HIWORD(lparam);
			window->mouse.OnLeftPressed(x, y);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			int x = LOWORD(lparam);
			int y = HIWORD(lparam);
			window->mouse.OnRightPressed(x, y);
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			int x = LOWORD(lparam);
			int y = HIWORD(lparam);
			window->mouse.OnMiddlePressed(x, y);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			int x = LOWORD(lparam);
			int y = HIWORD(lparam);
			window->mouse.OnLeftReleased(x, y);
			return 0;
		}
		case WM_RBUTTONUP:
		{
			int x = LOWORD(lparam);
			int y = HIWORD(lparam);
			window->mouse.OnRightReleased(x, y);
			return 0;
		}
		case WM_MBUTTONUP:
		{
			int x = LOWORD(lparam);
			int y = HIWORD(lparam);
			window->mouse.OnMiddleReleased(x, y);
			return 0;
		}

		case WM_MOUSEWHEEL:
		{
			int x = LOWORD(lparam);
			int y = HIWORD(lparam);
			if (GET_WHEEL_DELTA_WPARAM(wparam) > 0)
			{
				window->mouse.OnWheelUp(x, y);
			}
			else if (GET_WHEEL_DELTA_WPARAM(wparam) < 0)
			{
				window->mouse.OnWheelDown(x, y);
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
			}
			else 
			{
				const bool wasPressed = lparam & 0x40000000;
				if (!wasPressed)
				{
					window->keyboard.OnKeyPressed(keycode);
				}
			}
		
			return 0;
		}

		case WM_KEYUP:
		{
			unsigned char keycode = static_cast<unsigned char>(wparam);
			window->keyboard.OnKeyReleased(keycode);
			return 0;
		}

		case WM_CHAR:
		{
			unsigned char ch = static_cast<unsigned char>(wparam);
			if (window->keyboard.IsCharsAutoRepeat())
			{
				window->keyboard.OnChar(ch);
			}
			else
			{
				const bool wasPressed = lparam & 0x40000000;
				if (!wasPressed)
				{
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

	bool DirectX11Window::broadcast()
	{
		MSG msg;
		window->OnUpdate();
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
			this->contextcallback(0);
			return;
		}

		this->contextcallback(1);
	}

	void DirectX11Window::OnDestroy()
	{
		m_is_running = false;
	}

	DirectX11Window::~DirectX11Window()
	{
	}

}
