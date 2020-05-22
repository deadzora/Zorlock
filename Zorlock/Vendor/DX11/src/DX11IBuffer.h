#pragma once
#include <d3d11.h>
#include <vector>

namespace DX11Raz
{
	class DX11DeviceContext;

	class RazIndexBuffer
	{
	public:
		RazIndexBuffer();
		void Release();
		void SetIndexes(UINT* indices, UINT count);
		void SetIndexes(std::vector<DWORD> indices);
		~RazIndexBuffer();
	private:
		friend class DX11DeviceContext;
		std::vector<DWORD> vertices;
		ID3D11Buffer* m_buffer;
		UINT m_size_index;
		UINT m_size_list;
	};



}