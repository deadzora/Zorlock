#pragma once
#include <vector>
#include "DX11Graphics.h"
#include "DX11Math.h"

namespace ZorlockDX11
{
	class DirectX11VertexArray
	{
	public:
		DirectX11VertexArray();

		~DirectX11VertexArray();

	private:
		std::vector<Vertex> VertexArray;
		std::vector<DWORD> IndexArray;
	};

}