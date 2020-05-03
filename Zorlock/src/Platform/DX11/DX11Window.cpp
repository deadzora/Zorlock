#include "ZLpch.h"
#include "DX11Window.h"

#include "Zorlock/Events/ApplicationEvent.h"
#include "Zorlock/Events/MouseEvent.h"
#include "Zorlock/Events/KeyEvent.h"

#include "DX11Context.h"

namespace Zorlock {

	static bool s_X11Initialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		ZL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
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
	}

	void DX11Window::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
	}

	bool DX11Window::IsVSync() const
	{
		return m_Data.VSync;
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
		//TO-DO set use pointer function here

		SetVSync(true);

		//TO-DO set DX11 window callbacks here



	}

	void DX11Window::Shutdown()
	{
	}

}