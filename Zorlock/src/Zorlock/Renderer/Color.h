#pragma once
typedef float COLOR3ARRAY[3];
typedef float COLOR4ARRAY[4];
#define COLOR Zorlock::ColorRGB
#define COLOR4 Zorlock::ColorRGBA

namespace Zorlock {


	struct Vector3;
	struct Vector4;

	struct ColorRGB {
	public:
		float x, y, z;
	
		ColorRGB() : x(0),y(0),z(0)
		{};
		ColorRGB(float x, float y, float z) : x(x), y(y), z(z)
		{
		}
		ColorRGB(Vector3& v);

		//for template compatability
		ColorRGB(float x, float y, float z, float w) : x(x), y(y), z(z)
		{
			//ignore w
		}
		ColorRGB(float x, float y) : x(x), y(y), z(0)
		{
		}
		ColorRGB operator=(const ColorRGB& q) {
			x = q.x; y = q.y; z = q.z;  return *this;
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
		ColorRGB operator=(const COLOR3ARRAY q) {
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
		ColorRGBA(Vector3& v);
		ColorRGBA(Vector4& v);

	public:
		uint32_t ToColor()
		{
			uint32_t r = (uint32_t)(x * 255.0f);
			uint32_t g = (uint32_t)(y * 255.0f);
			uint32_t b = (uint32_t)(z * 255.0f);
			uint32_t a = (uint32_t)(w * 255.0f);

			return r << g | b << a;

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

		ColorRGBA Half()
		{
			this->x = 0.5f;
			this->y = 0.5f;
			this->z = 0.5f;
			this->w = 1.0f;
			return *this;
		};


		ColorRGBA Quarter()
		{
			this->x = 0.25f;
			this->y = 0.25f;
			this->z = 0.25f;
			this->w = 1.0f;
			return *this;
		};
		//need to add more colors

		static ColorRGBA WHITE()
		{
			return ColorRGBA().White();
		}

		static ColorRGBA BLUE()
		{
			return ColorRGBA().Blue();
		}

		static ColorRGBA HALF()
		{
			return ColorRGBA().Half();
		}

		static ColorRGBA QUARTER()
		{
			return ColorRGBA().Quarter();
		}

		static ColorRGBA BLACK()
		{
			return ColorRGBA().Black();
		}

		ColorRGBA operator=(const COLOR4ARRAY q) {
			x = q[0]; y = q[1]; z = q[2]; w = q[3];  return *this;
		}
		ColorRGBA operator=(const ColorRGBA& q) {
			x = q.x; y = q.y; z = q.z; w = q.w; return *this;
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
		float* ToArrayPTR()
		{
			static float vec4[4];
			vec4[0] = x;
			vec4[1] = y;
			vec4[2] = z;
			vec4[3] = z;

			return vec4;
		}

	};

}