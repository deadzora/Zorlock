#pragma once

#include "Zorlock/Window.h"
#include "Zorlock/Renderer/GraphicsContext.h"
#include <DirectX11Window.h>


namespace Zorlock {

class DX11Window : public Window
{
public:
	DX11Window(const WindowProps& props);
	virtual ~DX11Window();

	void OnUpdate() override;

	inline unsigned int GetWidth() const override { return m_Data.Width; }
	inline unsigned int GetHeight() const override { return m_Data.Height; }

	// Window attributes
	inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;

	inline virtual void* GetNativeWindow() const { return m_Window; }
	static void MouseCallback(ZorlockDX11::DirectX11Window* window, int button, int x, int y);
	static void ResizeCallback(ZorlockDX11::DirectX11Window* window, int width, int height);
	static void CloseCallback(ZorlockDX11::DirectX11Window* window);
	static void KeyCallBack(ZorlockDX11::DirectX11Window* window, int key, int scancode, int action, int mods);
	static void CharCallBack(ZorlockDX11::DirectX11Window* window, unsigned int keycode);
	static void ScrollCallBack(ZorlockDX11::DirectX11Window* window, double xOffset, double yOffset);
	static void MousePosCallBack(ZorlockDX11::DirectX11Window* window, double x, double y);
	void Init(const WindowProps& props);
	virtual void Shutdown();
private:
	ZorlockDX11::DirectX11Window* m_Window;
	GraphicsContext* m_Context;
	
	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;

		EventCallbackFn EventCallback;
	};

	WindowData m_Data;

};

}

