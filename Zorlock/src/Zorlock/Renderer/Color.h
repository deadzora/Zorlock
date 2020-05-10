#pragma once
#include "../Core/Math.h"

namespace Zorlock {

	struct ColorRGB {
		Vector3 value;
		ColorRGB() {};
		ColorRGB(float x, float y, float z) : value(Vector3(x, y, z))
		{
		}
		//for template compatability
		ColorRGB(float x, float y, float z, float w) : value(Vector3(x, y, z))
		{
			//ignore w
		}
		ColorRGB(float x, float y) : value(Vector3(x, y, 0))
		{
		}
		ColorRGB White()
		{
			this->value.x = 1.0f;
			this->value.y = 1.0f;
			this->value.z = 1.0f;
			return *this;
		}

		ColorRGB Black()
		{
			this->value.x = 0.0f;
			this->value.y = 0.0f;
			this->value.z = 0.0f;
			return *this;
		}

		ColorRGB Red()
		{
			this->value.x = 1.0f;
			this->value.y = 0.0f;
			this->value.z = 0.0f;
			return *this;
		}

		ColorRGB Green()
		{
			this->value.x = 0.0f;
			this->value.y = 1.0f;
			this->value.z = 0.0f;
			return *this;
		}

		ColorRGB Blue()
		{
			this->value.x = 0.0f;
			this->value.y = 0.0f;
			this->value.z = 0.0f;
			return *this;
		}

	};

	struct ColorRGBA {
		Vector4 value;
		ColorRGBA() {};
		ColorRGBA(float x, float y, float z, float w) : value(Vector4(x, y, z, w))
		{
		}
		ColorRGBA(float x, float y, float z) : value(Vector4(x, y, z, 0))
		{
		}
		ColorRGBA(float x, float y) : value(Vector4(x, y, 0, 0))
		{
		}
		ColorRGBA White()
		{
			this->value.x = 1.0f;
			this->value.y = 1.0f;
			this->value.z = 1.0f;
			this->value.w = 1.0f;
			return *this;
		};

		ColorRGBA Black()
		{
			this->value.x = 0.0f;
			this->value.y = 0.0f;
			this->value.z = 0.0f;
			this->value.w = 1.0f;
			return *this;
		};

		ColorRGBA Red()
		{
			this->value.x = 1.0f;
			this->value.y = 0.0f;
			this->value.z = 0.0f;
			this->value.w = 1.0f;
			return *this;
		};

		ColorRGBA Green()
		{
			this->value.x = 0.0f;
			this->value.y = 1.0f;
			this->value.z = 0.0f;
			this->value.w = 1.0f;
			return *this;
		};

		ColorRGBA Blue()
		{
			this->value.x = 0.0f;
			this->value.y = 0.0f;
			this->value.z = 0.0f;
			this->value.w = 1.0f;
			return *this;
		};


	};

}