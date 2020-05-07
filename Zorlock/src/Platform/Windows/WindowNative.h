#pragma once
#include "Zorlock/Core/Window.h"
#include "Zorlock/Renderer/GraphicsContext.h"
#include <DX11Raz.h>


namespace Zorlock {

	class WindowsNative : public Window
	{
	public:
		WindowsNative(const WindowProps& props);
		virtual ~WindowsNative();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		//may create a vector<ZWindow> to handle multiple
		DX11Raz::ZWindow* m_Window;
		Scope<GraphicsContext> m_Context;

		struct ZWindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		ZWindowData m_Data;
	};

}