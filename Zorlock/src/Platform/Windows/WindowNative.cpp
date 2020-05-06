#include "ZLpch.h"
#include "WindowNative.h"
#include "Zorlock/Renderer/Renderer.h"
namespace Zorlock
{
	static uint8_t s_NativeWindowCount = 0;

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
	}

	void WindowsNative::SetVSync(bool enabled)
	{
	}

	bool WindowsNative::IsVSync() const
	{
		return false;
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

		SetWindowUserPointer(m_Window, &m_Data);
	}

	void WindowsNative::Shutdown()
	{
	}

}
