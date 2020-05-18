#pragma once
#include <d3d11.h>
#include <vector>
#include "DX11Vertex.h"

namespace DX11Raz
{

	struct Vertex;

	class RazVertexBuffer
	{
	public:
		RazVertexBuffer();
		bool SetLayout();
		bool SetLayout(ID3D10Blob* vertexshader);
		void Release();		
		void SetIndex(uint32_t index);
		void SetIndexValue(UINT index , D3D11_INPUT_ELEMENT_DESC & value);
		void SetVertices(uint32_t size);
		void SetVertices(float* vertices, UINT size);
		void SetVertices(void* vertices, UINT size);
		void SetVertices(std::vector<RazVertex> & v);
		D3D11_INPUT_ELEMENT_DESC& GetLayoutPointer(UINT index);
		UINT GetVertexListSize();
		~RazVertexBuffer();
	private:
		UINT m_size_vertex;
		UINT m_size_list;
		std::vector<RazVertex> vertices;
		std::vector<D3D11_INPUT_ELEMENT_DESC> vlayout;
		ID3D11Buffer* m_buffer;
		ID3D11InputLayout* m_layout;


	};

}