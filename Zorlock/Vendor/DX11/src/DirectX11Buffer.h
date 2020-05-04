#pragma once
#include <d3d11.h>

namespace ZorlockDX11
{
	
	class DirectX11Buffer
	{
	public:
		bool Bind(void* m_list, unsigned int m_size);


	private:

		unsigned int m_size;
		ID3D11Buffer* m_buffer;
		ID3D11InputLayout* m_layout;
	};
	
}