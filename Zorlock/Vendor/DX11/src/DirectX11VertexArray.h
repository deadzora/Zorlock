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
		unsigned int GetRenderID()
		{
			return Renderid;
		};
		void SetRenderID(unsigned int i)
		{
			Renderid = i;
		};
	private:
		unsigned int Renderid;
		std::vector<Vertex> VertexArray;
		std::vector<DWORD> IndexArray;
	};

}