#pragma once
#include <d3d11.h>

class DeviceContext;

class IndexBuffer
{
public:
	IndexBuffer();
	bool load(void* list_index, UINT size_vertex, UINT size_list);
	UINT GetIndexListSize();
	bool release();
	~IndexBuffer();
private:
	UINT m_size_index = 0;
	UINT m_size_list = 0;
	ID3D11Buffer* m_buffer = nullptr;
	friend class DeviceContext;
};

