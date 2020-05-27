#include "ZLpch.h"
#include "WindowsNativeInput.h"
#include "Zorlock/Core/Application.h"
#include "ZWindow.h"

namespace Zorlock
{

	bool WindowsNativeInput::IsKeyPressedImpl(KeyCode key)
	{
		DX11Raz::ZWindow * window = static_cast<DX11Raz::ZWindow*>(Application::Get().GetWindow().GetNativeWindow());
		bool ispressed = window->keyboard.KeyIsPressed((unsigned char)key);
		if (ispressed)
		{
			if (window->keyboard.IsKeysAutoRepeat())
			{
				return 2;
			}
			else
			{
				return 1;
			}
		}
		return 0;
	}

	bool WindowsNativeInput::IsMouseButtonPressedImpl(MouseCode button)
	{
		DX11Raz::ZWindow* window = static_cast<DX11Raz::ZWindow*>(Application::Get().GetWindow().GetNativeWindow());
		switch (button)
		{
		case MouseCode::ButtonLeft:
		{
			return window->mouse.IsLeftDown();
			break;
		}
		case MouseCode::ButtonRight:
		{
			return window->mouse.IsRightDown();
			break;
		}
		case MouseCode::ButtonMiddle:
		{
			return window->mouse.IsMiddleDown();
			break;
		}
		}
		
		return false;
	}

	std::pair<float, float> WindowsNativeInput::GetMousePositionImpl()
	{
		DX11Raz::ZWindow* window = static_cast<DX11Raz::ZWindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		MousePoint point = window->mouse.GetPos();
		xpos = point.x;
		ypos = point.y;
		return { (float)xpos, (float)ypos };
	}

	float WindowsNativeInput::GetMouseXImpl()
	{
		DX11Raz::ZWindow* window = static_cast<DX11Raz::ZWindow*>(Application::Get().GetWindow().GetNativeWindow());
		return window->mouse.GetPosX();
	}

	float WindowsNativeInput::GetMouseYImpl()
	{
		DX11Raz::ZWindow* window = static_cast<DX11Raz::ZWindow*>(Application::Get().GetWindow().GetNativeWindow());
		return window->mouse.GetPosY();
	}


}
