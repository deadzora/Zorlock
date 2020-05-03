#pragma once
#include "VertexBuffer.h"

class CalVertexBuffer : public VertexBuffer
{
public:
	CalVertexBuffer();
	bool setlayout(void* shader_byte_code, UINT size_byte_shader) override;
	bool load(void * list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader) override;
	~CalVertexBuffer();
};

