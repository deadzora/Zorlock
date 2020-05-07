#include "ZLpch.h"
#include "WindowNative.h"
#include "Zorlock/Renderer/Renderer.h"
#include "Zorlock/Events/ApplicationEvent.h"
#include "Zorlock/Events/MouseEvent.h"
#include "Zorlock/Events/KeyEvent.h"


namespace Zorlock
{
	static uint8_t s_NativeWindowCount = 0;


	void WindowsNative::Shutdown()
	{
		ZL_PROFILE_FUNCTION();

		DX11Raz::ZDestroyWindow(m_Window);
		--s_NativeWindowCount;

		if (s_NativeWindowCount == 0)
		{
			DX11Raz::ZTerminate();
		}
	}

	static void Win32ErrorCallback(int error, const char* description)
	{
		ZL_CORE_ERROR("Win32 Error ({0}): {1}", error, description);
	}

	WindowsNative::WindowsNative(const WindowProps& props)
	{
		ZL_PROFILE_FUNCTION();
		Init(props);
	}

	WindowsNative::~WindowsNative()
	{
		ZL_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsNative::OnUpdate()
	{
		ZL_PROFILE_FUNCTION();

		m_Window->PollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsNative::SetVSync(bool enabled)
	{
		ZL_PROFILE_FUNCTION();

		//if (enabled)
			//glfwSwapInterval(1);
		//else
			//glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsNative::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsNative::Init(const WindowProps& props)
	{
		ZL_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ZL_CORE_INFO("Creating Raz Native window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_NativeWindowCount == 0)
		{
			ZL_PROFILE_SCOPE("Zwin32Init");
			int success = DX11Raz::InitZWindows();
			ZL_CORE_ASSERT(success, "Could not initialize Raz Native Windows!");
			DX11Raz::SetZWindowCallback(Win32ErrorCallback);
		}

		ZL_PROFILE_SCOPE("ZCreateWindow");
#if defined(ZL_DEBUG)
		if (Renderer::GetAPI() == RendererAPI::API::DX11)
		{
			//nothing to see here. my library checks for ZL_DEBUG
		}
#endif
		std::wstring stitle = std::wstring(m_Data.Title.begin(), m_Data.Title.end());
		m_Window = DX11Raz::ZCreateWindow((UINT)props.Width, (UINT)props.Height, stitle.c_str());
		++s_NativeWindowCount;

		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		DX11Raz::SetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Set Raz Windows Callbacks
		DX11Raz::ZSetWindowSizeCallback(m_Window, [](DX11Raz::ZWin* window, int width, int height)
			{
				DX11Raz::ZWindow* win = ZWINDOW(window);
				ZWindowData& data = *(ZWindowData*)GetWindowUserPointer(win);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		DX11Raz::ZSetCloseCallback(m_Window, [](DX11Raz::ZWin* window)
			{

				DX11Raz::ZWindow* win = ZWINDOW(window);
				ZWindowData& data = *(ZWindowData*)GetWindowUserPointer(win);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		DX11Raz::ZSetKeyCallback(m_Window, [](DX11Raz::ZWin* window, int key, int scancode, int action, int mods)
			{
				DX11Raz::ZWindow* win = ZWINDOW(window);
				ZWindowData& data = *(ZWindowData*)GetWindowUserPointer(win);

				switch (action)
				{
				case DX11Raz::DX_KEYACTION::DX_PRESS:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.EventCallback(event);
					break;
				}
				case DX11Raz::DX_KEYACTION::DX_RELEASE:
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.EventCallback(event);
					break;
				}
				case DX11Raz::DX_KEYACTION::DX_REPEATE:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		DX11Raz::ZSetCharacterCallback(m_Window, [](DX11Raz::ZWin* window, unsigned int keycode)
			{
				DX11Raz::ZWindow* win = ZWINDOW(window);
				ZWindowData& data = *(ZWindowData*)GetWindowUserPointer(win);

				KeyTypedEvent event(static_cast<KeyCode>(keycode));
				data.EventCallback(event);
			});

		DX11Raz::ZSetMouseButtonCallback(m_Window, [](DX11Raz::ZWin* window, int button, int action, int mods)
			{
				DX11Raz::ZWindow* win = ZWINDOW(window);
				ZWindowData& data = *(ZWindowData*)GetWindowUserPointer(win);

				switch (button)
				{
				case WM_LBUTTONDOWN:
				{
					MouseButtonPressedEvent event(MouseCode::Button0);
					data.EventCallback(event);
					break;
				}
				case WM_RBUTTONDOWN:
				{
					MouseButtonPressedEvent event(MouseCode::Button1);
					data.EventCallback(event);
					break;
				}
				case WM_MBUTTONDOWN:
				{
					MouseButtonPressedEvent event(MouseCode::Button2);
					data.EventCallback(event);
					break;
				}
				case WM_LBUTTONUP:
				{
					MouseButtonReleasedEvent event(MouseCode::Button0);
					data.EventCallback(event);
					break;
				}
				case WM_RBUTTONUP:
				{
					MouseButtonReleasedEvent event(MouseCode::Button1);
					data.EventCallback(event);
					break;
				}
				case WM_MBUTTONUP:
				{
					MouseButtonReleasedEvent event(MouseCode::Button2);
					data.EventCallback(event);
					break;
				}
				}
			});

		DX11Raz::ZSetScrollCallback(m_Window, [](DX11Raz::ZWin* window, double xOffset, double yOffset)
			{
				DX11Raz::ZWindow* win = ZWINDOW(window);
				ZWindowData& data = *(ZWindowData*)GetWindowUserPointer(win);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		DX11Raz::ZSetMousePosCallback(m_Window, [](DX11Raz::ZWin* window, double xPos, double yPos)
			{
				DX11Raz::ZWindow* win = ZWINDOW(window);
				ZWindowData& data = *(ZWindowData*)GetWindowUserPointer(win);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});

	}



}