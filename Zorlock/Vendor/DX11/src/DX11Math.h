#pragma once

namespace ZorlockDX11
{
	static class DX11Math
	{
	public:
		static float DegreesFromRadians(float r)
		{
			return r * 180.0f / 3.141592653589793238463f;
		};

		static float RadiansFromDegrees(float d)
		{
			return d * 3.141592653589793238463f / 180;
		};

	};

	struct Vector2 {
		float x, y;
		Vector2() : x(0), y{ 0 } {} ;
	};

	struct Vector3 : public Vector2 {
	public:
		float z;
		Vector3() : z(0) {};

	};

	struct Vector4 : public Vector3 {
		float w;
		Vector4() : w(0) {};
	};

	struct Vertex
	{
		Vertex() {
			this->position.x = 0;
			this->position.y = 0;
			this->position.z = 0;
			this->normal.x = 0;
			this->normal.y = 0;
			this->normal.z = 0;
			this->uvw.x = 0;
			this->uvw.y = 0;
			this->uvw.z = 0;
		};
		Vertex(float x, float y, float z)
		{
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
			this->normal.x = 0;
			this->normal.y = 0;
			this->normal.z = 0;
			this->uvw.x = 0;
			this->uvw.y = 0;
			this->uvw.z = 0;
		};
		Vertex(float x, float y, float z, float u, float v, float w)
		{
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
			this->uvw.x = u;
			this->uvw.y = v;
			this->uvw.z = w;
			this->normal.x = 0;
			this->normal.y = 0;
			this->normal.z = 0;
		};
		Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v, float w)
		{
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
			this->normal.x = nx;
			this->normal.y = ny;
			this->normal.z = nz;
			this->uvw.x = u;
			this->uvw.y = v;
			this->uvw.z = w;
		};

		Vector3 position;
		Vector3 normal;
		Vector3 color;
		Vector3 uvw;

	};
}