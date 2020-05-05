#pragma once

namespace Zorlock
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define ZL_KEY_SPACE           ::Zorlock::Key::Space
#define ZL_KEY_APOSTROPHE      ::Zorlock::Key::Apostrophe    /* ' */
#define ZL_KEY_COMMA           ::Zorlock::Key::Comma         /* , */
#define ZL_KEY_MINUS           ::Zorlock::Key::Minus         /* - */
#define ZL_KEY_PERIOD          ::Zorlock::Key::Period        /* . */
#define ZL_KEY_SLASH           ::Zorlock::Key::Slash         /* / */
#define ZL_KEY_0               ::Zorlock::Key::D0
#define ZL_KEY_1               ::Zorlock::Key::D1
#define ZL_KEY_2               ::Zorlock::Key::D2
#define ZL_KEY_3               ::Zorlock::Key::D3
#define ZL_KEY_4               ::Zorlock::Key::D4
#define ZL_KEY_5               ::Zorlock::Key::D5
#define ZL_KEY_6               ::Zorlock::Key::D6
#define ZL_KEY_7               ::Zorlock::Key::D7
#define ZL_KEY_8               ::Zorlock::Key::D8
#define ZL_KEY_9               ::Zorlock::Key::D9
#define ZL_KEY_SEMICOLON       ::Zorlock::Key::Semicolon     /* ; */
#define ZL_KEY_EQUAL           ::Zorlock::Key::Equal         /* = */
#define ZL_KEY_A               ::Zorlock::Key::A
#define ZL_KEY_B               ::Zorlock::Key::B
#define ZL_KEY_C               ::Zorlock::Key::C
#define ZL_KEY_D               ::Zorlock::Key::D
#define ZL_KEY_E               ::Zorlock::Key::E
#define ZL_KEY_F               ::Zorlock::Key::F
#define ZL_KEY_G               ::Zorlock::Key::G
#define ZL_KEY_H               ::Zorlock::Key::H
#define ZL_KEY_I               ::Zorlock::Key::I
#define ZL_KEY_J               ::Zorlock::Key::J
#define ZL_KEY_K               ::Zorlock::Key::K
#define ZL_KEY_L               ::Zorlock::Key::L
#define ZL_KEY_M               ::Zorlock::Key::M
#define ZL_KEY_N               ::Zorlock::Key::N
#define ZL_KEY_O               ::Zorlock::Key::O
#define ZL_KEY_P               ::Zorlock::Key::P
#define ZL_KEY_Q               ::Zorlock::Key::Q
#define ZL_KEY_R               ::Zorlock::Key::R
#define ZL_KEY_S               ::Zorlock::Key::S
#define ZL_KEY_T               ::Zorlock::Key::T
#define ZL_KEY_U               ::Zorlock::Key::U
#define ZL_KEY_V               ::Zorlock::Key::V
#define ZL_KEY_W               ::Zorlock::Key::W
#define ZL_KEY_X               ::Zorlock::Key::X
#define ZL_KEY_Y               ::Zorlock::Key::Y
#define ZL_KEY_Z               ::Zorlock::Key::Z
#define ZL_KEY_LEFT_BRACKET    ::Zorlock::Key::LeftBracket   /* [ */
#define ZL_KEY_BACKSLASH       ::Zorlock::Key::Backslash     /* \ */
#define ZL_KEY_RIGHT_BRACKET   ::Zorlock::Key::RightBracket  /* ] */
#define ZL_KEY_GRAVE_ACCENT    ::Zorlock::Key::GraveAccent   /* ` */
#define ZL_KEY_WORLD_1         ::Zorlock::Key::World1        /* non-US #1 */
#define ZL_KEY_WORLD_2         ::Zorlock::Key::World2        /* non-US #2 */

/* Function keys */
#define ZL_KEY_ESCAPE          ::Zorlock::Key::Escape
#define ZL_KEY_ENTER           ::Zorlock::Key::Enter
#define ZL_KEY_TAB             ::Zorlock::Key::Tab
#define ZL_KEY_BACKSPACE       ::Zorlock::Key::Backspace
#define ZL_KEY_INSERT          ::Zorlock::Key::Insert
#define ZL_KEY_DELETE          ::Zorlock::Key::Delete
#define ZL_KEY_RIGHT           ::Zorlock::Key::Right
#define ZL_KEY_LEFT            ::Zorlock::Key::Left
#define ZL_KEY_DOWN            ::Zorlock::Key::Down
#define ZL_KEY_UP              ::Zorlock::Key::Up
#define ZL_KEY_PAGE_UP         ::Zorlock::Key::PageUp
#define ZL_KEY_PAGE_DOWN       ::Zorlock::Key::PageDown
#define ZL_KEY_HOME            ::Zorlock::Key::Home
#define ZL_KEY_END             ::Zorlock::Key::End
#define ZL_KEY_CAPS_LOCK       ::Zorlock::Key::CapsLock
#define ZL_KEY_SCROLL_LOCK     ::Zorlock::Key::ScrollLock
#define ZL_KEY_NUM_LOCK        ::Zorlock::Key::NumLock
#define ZL_KEY_PRINT_SCREEN    ::Zorlock::Key::PrintScreen
#define ZL_KEY_PAUSE           ::Zorlock::Key::Pause
#define ZL_KEY_F1              ::Zorlock::Key::F1
#define ZL_KEY_F2              ::Zorlock::Key::F2
#define ZL_KEY_F3              ::Zorlock::Key::F3
#define ZL_KEY_F4              ::Zorlock::Key::F4
#define ZL_KEY_F5              ::Zorlock::Key::F5
#define ZL_KEY_F6              ::Zorlock::Key::F6
#define ZL_KEY_F7              ::Zorlock::Key::F7
#define ZL_KEY_F8              ::Zorlock::Key::F8
#define ZL_KEY_F9              ::Zorlock::Key::F9
#define ZL_KEY_F10             ::Zorlock::Key::F10
#define ZL_KEY_F11             ::Zorlock::Key::F11
#define ZL_KEY_F12             ::Zorlock::Key::F12
#define ZL_KEY_F13             ::Zorlock::Key::F13
#define ZL_KEY_F14             ::Zorlock::Key::F14
#define ZL_KEY_F15             ::Zorlock::Key::F15
#define ZL_KEY_F16             ::Zorlock::Key::F16
#define ZL_KEY_F17             ::Zorlock::Key::F17
#define ZL_KEY_F18             ::Zorlock::Key::F18
#define ZL_KEY_F19             ::Zorlock::Key::F19
#define ZL_KEY_F20             ::Zorlock::Key::F20
#define ZL_KEY_F21             ::Zorlock::Key::F21
#define ZL_KEY_F22             ::Zorlock::Key::F22
#define ZL_KEY_F23             ::Zorlock::Key::F23
#define ZL_KEY_F24             ::Zorlock::Key::F24
#define ZL_KEY_F25             ::Zorlock::Key::F25

/* Keypad */
#define ZL_KEY_KP_0            ::Zorlock::Key::KP0
#define ZL_KEY_KP_1            ::Zorlock::Key::KP1
#define ZL_KEY_KP_2            ::Zorlock::Key::KP2
#define ZL_KEY_KP_3            ::Zorlock::Key::KP3
#define ZL_KEY_KP_4            ::Zorlock::Key::KP4
#define ZL_KEY_KP_5            ::Zorlock::Key::KP5
#define ZL_KEY_KP_6            ::Zorlock::Key::KP6
#define ZL_KEY_KP_7            ::Zorlock::Key::KP7
#define ZL_KEY_KP_8            ::Zorlock::Key::KP8
#define ZL_KEY_KP_9            ::Zorlock::Key::KP9
#define ZL_KEY_KP_DECIMAL      ::Zorlock::Key::KPDecimal
#define ZL_KEY_KP_DIVIDE       ::Zorlock::Key::KPDivide
#define ZL_KEY_KP_MULTIPLY     ::Zorlock::Key::KPMultiply
#define ZL_KEY_KP_SUBTRACT     ::Zorlock::Key::KPSubtract
#define ZL_KEY_KP_ADD          ::Zorlock::Key::KPAdd
#define ZL_KEY_KP_ENTER        ::Zorlock::Key::KPEnter
#define ZL_KEY_KP_EQUAL        ::Zorlock::Key::KPEqual

#define ZL_KEY_LEFT_SHIFT      ::Zorlock::Key::LeftShift
#define ZL_KEY_LEFT_CONTROL    ::Zorlock::Key::LeftControl
#define ZL_KEY_LEFT_ALT        ::Zorlock::Key::LeftAlt
#define ZL_KEY_LEFT_SUPER      ::Zorlock::Key::LeftSuper
#define ZL_KEY_RIGHT_SHIFT     ::Zorlock::Key::RightShift
#define ZL_KEY_RIGHT_CONTROL   ::Zorlock::Key::RightControl
#define ZL_KEY_RIGHT_ALT       ::Zorlock::Key::RightAlt
#define ZL_KEY_RIGHT_SUPER     ::Zorlock::Key::RightSuper
#define ZL_KEY_MENU            ::Zorlock::Key::Menu
