#pragma once

namespace Zorlock
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,

		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
	} Mouse;
	
	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define ZL_MOUSE_BUTTON_0      ::Zorlock::Mouse::Button0
#define ZL_MOUSE_BUTTON_1      ::Zorlock::Mouse::Button1
#define ZL_MOUSE_BUTTON_2      ::Zorlock::Mouse::Button2
#define ZL_MOUSE_BUTTON_3      ::Zorlock::Mouse::Button3
#define ZL_MOUSE_BUTTON_4      ::Zorlock::Mouse::Button4
#define ZL_MOUSE_BUTTON_5      ::Zorlock::Mouse::Button5
#define ZL_MOUSE_BUTTON_6      ::Zorlock::Mouse::Button6
#define ZL_MOUSE_BUTTON_7      ::Zorlock::Mouse::Button7
#define ZL_MOUSE_BUTTON_LAST   ::Zorlock::Mouse::ButtonLast
#define ZL_MOUSE_BUTTON_LEFT   ::Zorlock::Mouse::ButtonLeft
#define ZL_MOUSE_BUTTON_RIGHT  ::Zorlock::Mouse::ButtonRight
#define ZL_MOUSE_BUTTON_MIDDLE ::Zorlock::Mouse::ButtonMiddle
