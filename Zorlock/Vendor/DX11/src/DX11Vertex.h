#pragma once


namespace DX11Raz
{
	struct RazVector3
	{
		float x, y, z;
		RazVector3() : x(0), y(0), z(0)
		{

		}
	};

	struct RazVertex
	{
		RazVertex() {};
		RazVertex(float x, float y, float z)
		{
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
		};
		RazVertex(float x, float y, float z, float u, float v, float w)
		{
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
			this->uvw.x = u;
			this->uvw.y = v;
			this->uvw.z = w;
		};
		RazVertex(float x, float y, float z, float nx, float ny, float nz, float u, float v, float w)
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

		RazVector3 position;
		RazVector3 normal;
		RazVector3 color;
		RazVector3 uvw;

	};


}