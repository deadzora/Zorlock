#pragma once
#include "VertexArray.h"
#include "Material.h"

namespace Zorlock {
	
	class Mesh
	{
	public:
		Mesh();
		~Mesh() {};
		void CreateVertexArray();
		void CreateVertexBuffer(float* vertices, uint32_t size);
		void CreateVertexBuffer(Vertex* vertices, uint32_t size);
		void CreateVertexBuffer(void* vertices, uint32_t size);
		void CreateIndexBuffer(uint32_t* indices, uint32_t count);
		Ref<VertexArray> GetVertexArray();

		void Bind();
		MATRIX4 GetMatrix();
		MATRIX4 GetDrawMatrix();
		void SetMatrix(MATRIX4 transform);
		void SetDrawMatrix(MATRIX4 transform);
		void SetMaterial(Ref<Material> material);
		void SetLayout(const BufferLayout& layout);
		void SetLayout(const BufferLayout& layout, Ref<Shader> shader);
		void SetLayout(const BufferLayout& layout, Ref<Material> material);
		void Draw();
		void Destroy();
		uint32_t vcount;
	protected:
		MATRIX4 drawMatrix;
		MATRIX4 transformMatrix;
		
		Ref<Material> m_material;
		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
	
	
}

#define ZLMESH Zorlock::Mesh