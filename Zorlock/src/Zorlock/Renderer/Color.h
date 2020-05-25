#pragma once
#define COLOR ColorRGB
#define COLOR4 ColorRGBA
typedef float COLOR3ARRAY[3];
typedef float COLOR4ARRAY[4];

namespace Zorlock {

	struct ColorRGB {
	public:
		float x, y, z;
	
		ColorRGB() = default;
		ColorRGB(float x, float y, float z) : x(x), y(y), z(z)
		{
		}
		//for template compatability
		ColorRGB(float x, float y, float z, float w) : x(x), y(y), z(z)
		{
			//ignore w
		}
		ColorRGB(float x, float y) : x(x), y(y), z(0)
		{
		}
	public:
		ColorRGB White()
		{
			this->x = 1.0f;
			this->y = 1.0f;
			this->z = 1.0f;
			return *this;
		}

		ColorRGB Black()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			return *this;
		}

		ColorRGB Red()
		{
			this->x = 1.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			return *this;
		}

		ColorRGB Green()
		{
			this->x = 0.0f;
			this->y = 1.0f;
			this->z = 0.0f;
			return *this;
		}

		ColorRGB Blue()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			return *this;
		}
		ColorRGB& operator=(const COLOR3ARRAY q) {
			x = q[0]; y = q[1]; z = q[2];  return *this;
		}
		COLOR3ARRAY& ToArray()
		{
			COLOR3ARRAY vec3;
			vec3[0] = x;
			vec3[1] = y;
			vec3[2] = z;


			return vec3;

		}
		Vector3 ToVector3()
		{
			return Vector3(x, y, z);
		}
	};

	struct ColorRGBA {

		float x, y, z, w;
	
		ColorRGBA() : x(0), y(0), z(0), w(1) {};
		ColorRGBA(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
		{
		}
		ColorRGBA(float x, float y, float z) : x(x), y(y), z(z), w(1)
		{
		}
	public:
		uint32_t ToColor()
		{
			uint32_t r = x * 255.0f;
			uint32_t g = y * 255.0f;
			uint32_t b = z * 255.0f;
			uint32_t a = w * 255.0f;

			return r << g | b << a;

		}
		static ColorRGBA WHITE()
		{
			return ColorRGBA().White();
		}

		ColorRGBA White()
		{
			this->x = 1.0f;
			this->y = 1.0f;
			this->z = 1.0f;
			this->w = 1.0f;
			return *this;
		};

		ColorRGBA Black()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			this->w = 1.0f;
			return *this;
		};

		ColorRGBA Red()
		{
			this->x = 1.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			this->w = 1.0f;
			return *this;
		};

		ColorRGBA Green()
		{
			this->x = 0.0f;
			this->y = 1.0f;
			this->z = 0.0f;
			this->w = 1.0f;
			return *this;
		};

		ColorRGBA Blue()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			this->w = 1.0f;
			return *this;
		};

		ColorRGBA& operator=(const COLOR4ARRAY q) {
			x = q[0]; y = q[1]; z = q[2]; w = q[3];  return *this;
		}
		COLOR4ARRAY& ToArray()
		{
			COLOR4ARRAY vec4;
			vec4[0] = x;
			vec4[1] = y;
			vec4[2] = z;
			vec4[3] = z;

			return vec4;

		}
		Vector4 ToVector4()
		{
			return Vector4(x, y, z,w);
		}

		Vector3 ToVector3()
		{
			return Vector3(x, y, z);
		}
	};

}