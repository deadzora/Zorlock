#include "ZLpch.h"
#include "DX11Window.h"

#include "Zorlock/Events/ApplicationEvent.h"
#include "Zorlock/Events/MouseEvent.h"
#include "Zorlock/Events/KeyEvent.h"

#include "DX11Context.h"

namespace Zorlock {

	static bool s_X11Initialized = false;

	static void DX11ErrorCallback(int error, const char* description)
	{
		ZL_CORE_ERROR("DX11 Error ({0}): {1}", error, description);
	}

	DX11Window::DX11Window(const WindowProps& props)
	{
		Init(props);
	}

	DX11Window::~DX11Window()
	{
		Shutdown();
	}

	void DX11Window::OnUpdate()
	{
		this->m_Window->DX11PollEvents();
		this->m_Context->SwapBuffers();
	}

	void DX11Window::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
	}

	bool DX11Window::IsVSync() const
	{
		return m_Data.VSync;
	}

	void DX11Window::MouseCallback(ZorlockDX11::DirectX11Window* window, int button, int x, int y)
	{
		WindowData& data = *(WindowData*)ZorlockDX11::DX11GetWindowUserPointer(window);

		switch (button)
		{
			case WM_LBUTTONDOWN:
			{
				MouseButtonPressedEvent event(0);
				data.EventCallback(event);
				break;
			}
			case WM_RBUTTONDOWN:
			{
				MouseButtonPressedEvent event(1);
				data.EventCallback(event);
				break;
			}
			case WM_MBUTTONDOWN:
			{
				MouseButtonPressedEvent event(2);
				data.EventCallback(event);
				break;
			}
			case WM_LBUTTONUP:
			{
				MouseButtonReleasedEvent event(0);
				data.EventCallback(event);
				break;
			}
			case WM_RBUTTONUP:
			{
				MouseButtonReleasedEvent event(1);
				data.EventCallback(event);
				break;
			}
			case WM_MBUTTONUP:
			{
				MouseButtonReleasedEvent event(2);
				data.EventCallback(event);
				break;
			}
		}
	}

	void DX11Window::ResizeCallback(ZorlockDX11::DirectX11Window* window, int width, int height)
	{
		WindowData& data = *(WindowData*)ZorlockDX11::DX11GetWindowUserPointer(window);
		data.Width = width;
		data.Height = height;

		WindowResizeEvent event(width, height);
		data.EventCallback(event);
	}

	void DX11Window::CloseCallback(ZorlockDX11::DirectX11Window* window)
	{
		WindowData& data = *(WindowData*)ZorlockDX11::DX11GetWindowUserPointer(window);
		WindowCloseEvent event;
		data.EventCallback(event);
	}

	void DX11Window::KeyCallBack(ZorlockDX11::DirectX11Window* window, int key, int scancode, int action, int mods)
	{
		WindowData& data = *(WindowData*)ZorlockDX11::DX11GetWindowUserPointer(window);

		switch (action)
		{
			case ZorlockDX11::DX_KEYACTION::DX_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case ZorlockDX11::DX_KEYACTION::DX_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case ZorlockDX11::DX_KEYACTION::DX_REPEATE:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
		}

	}

	void DX11Window::CharCallBack(ZorlockDX11::DirectX11Window* window, unsigned int keycode)
	{
		WindowData& data = *(WindowData*)ZorlockDX11::DX11GetWindowUserPointer(window);
		KeyTypedEvent event(keycode);
		data.EventCallback(event);
	}

	void DX11Window::ScrollCallBack(ZorlockDX11::DirectX11Window* window, double xOffset, double yOffset)
	{
		WindowData& data = *(WindowData*)ZorlockDX11::DX11GetWindowUserPointer(window);
		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		data.EventCallback(event);
	}

	void DX11Window::MousePosCallBack(ZorlockDX11::DirectX11Window* window, double x, double y)
	{
		WindowData& data = *(WindowData*)ZorlockDX11::DX11GetWindowUserPointer(window);
		MouseMovedEvent event((float)x, (float)y);
		data.EventCallback(event);
	}

	void DX11Window::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ZL_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		m_Window = new ZorlockDX11::DirectX11Window();
		m_Window->init((int)props.Width, (int)props.Height, props.Title);
		m_Context = new DX11Context(m_Window);
		m_Context->Init();
		ZorlockDX11::DX11SetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Set DX11 Callbacks here, wrote them to marginally match GLFW counterparts
		ZorlockDX11::DX11SetMouseButtonCallback(DX11Window::MouseCallback);
		ZorlockDX11::DX11SetWindowSizeCallback(DX11Window::ResizeCallback);
		ZorlockDX11::DX11SetKeyCallback(DX11Window::KeyCallBack);
		ZorlockDX11::DX11SetCharacterCallback(DX11Window::CharCallBack);
		ZorlockDX11::DX11SetScrollCallback(DX11Window::ScrollCallBack);
		ZorlockDX11::DX11SetMousePosCallback(DX11Window::MousePosCallBack);
	}

	void DX11Window::Shutdown()
	{
		//Change this to shut down all GFX systems
		m_Window->release();
	}

}