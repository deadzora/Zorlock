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
private:
	virtual void MouseCallback(ZorlockDX11::DirectX11Window* window, int button, int x, int y);
	virtual void ResizeCallback(ZorlockDX11::DirectX11Window* window, int width, int height);
	virtual void CloseCallback(ZorlockDX11::DirectX11Window* window);
	virtual void KeyCallBack(ZorlockDX11::DirectX11Window* window, int key, int scancode, int action, int mods);
	virtual void CharCallBack(ZorlockDX11::DirectX11Window* window, unsigned int keycode);
	virtual void ScrollCallBack(ZorlockDX11::DirectX11Window* window, double xOffset, double yOffset);
	virtual void MousePosCallBack(ZorlockDX11::DirectX11Window* window, double x, double y);
	virtual void Init(const WindowProps& props);
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

