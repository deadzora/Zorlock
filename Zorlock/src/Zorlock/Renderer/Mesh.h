#pragma once
#include "VertexArray.h"
#include "Material.h"

namespace Zorlock {
	
	class Mesh
	{
	public:
		Mesh();
		Mesh(std::string name);
		~Mesh() {};
		Ref<VertexArray> CreateVertexArray();
		Ref<VertexBuffer> CreateVertexBuffer(float* vertices, uint32_t size);
		Ref<VertexBuffer> CreateVertexBuffer(Vertex* vertices, uint32_t size);
		Ref<VertexBuffer> CreateVertexBuffer(void* vertices, uint32_t size);
		Ref<IndexBuffer> CreateIndexBuffer(uint32_t* indices, uint32_t count);
		Ref<VertexArray> GetVertexArray();

		void Bind();
		MATRIX4 GetMatrix();
		MATRIX4 GetDrawMatrix();
		void SetMatrix(MATRIX4 transform);
		void SetDrawMatrix(MATRIX4 transform);
		void SetMaterial(Ref<Material> material);
		Ref<Material> GetMaterial();
		void SetLayout(const BufferLayout& layout);
		void SetLayout(const BufferLayout& layout, Ref<Shader> shader);
		void SetLayout(const BufferLayout& layout, Ref<Material> material);
		void Draw();
		void Destroy();
		void SetMeshID(uint32_t i);
		uint32_t GetMeshID();

		uint32_t vcount;
		std::string name;
		bool hasbones;
	protected:
		
		MATRIX4 drawMatrix;
		MATRIX4 transformMatrix;
		uint32_t m_meshID;
		Ref<Material> m_material;
		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
	
	
}

#define ZLMESH Zorlock::Mesh