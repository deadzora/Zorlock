#pragma once

#include "Zorlock/Core/Input.h"

namespace Zorlock {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) override;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}
