#include "ZLpch.h"
#include "Math.h"
#include "Zorlock/Renderer/Color.h"
namespace Zorlock
{




	Vector3::Vector3(ColorRGB& c) : x(c.x), y(c.y), z(c.z)
	{
	}

	Vector4::Vector4(ColorRGB& c) : x(c.x), y(c.y), z(c.z), w(1.0f)
	{
	}

	Vector4::Vector4(ColorRGBA& c) : x(c.x), y(c.y), z(c.z), w(c.w)
	{

	}

}
