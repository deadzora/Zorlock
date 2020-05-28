#include "ZLpch.h"
#include "Color.h"
#include "Zorlock/Core/Math.h"
namespace Zorlock
{
	ColorRGB::ColorRGB(Vector3& v) : x(v.x), y(v.y), z(v.z)
	{
	}


	ColorRGBA::ColorRGBA(Vector3& v) : x(v.x), y(v.y), z(v.z), w(1.0f)
	{
	}

	ColorRGBA::ColorRGBA(Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w)
	{
	}

}
