#include "ZLpch.h"
#include "Mesh.h"
#include "Zorlock/Renderer/Renderer.h"


namespace Zorlock
{
	Mesh::Mesh() : drawMatrix(MATRIX4::IDENTITY()), transformMatrix(MATRIX4::IDENTITY()), vcount(0), hasbones(false), m_meshID(0), name("mesh")
	{
	}
	Mesh::Mesh(std::string name) : drawMatrix(MATRIX4::IDENTITY()), transformMatrix(MATRIX4::IDENTITY()), vcount(0), hasbones(false), m_meshID(0), name(name)
	{
	}
	Ref<VertexArray> Mesh::CreateVertexArray()
	{
		m_VertexArray = VertexArray::Create();
		return m_VertexArray;
	}

	Ref<VertexBuffer> Mesh::CreateVertexBuffer(float* vertices, uint32_t size)
	{
		m_VertexBuffer = VertexBuffer::Create(vertices, size);
		return m_VertexBuffer;
	}

	Ref<VertexBuffer> Mesh::CreateVertexBuffer(Vertex* vertices, uint32_t size)
	{
		m_VertexBuffer = VertexBuffer::Create(vertices, size);
		return m_VertexBuffer;
	}

	Ref<VertexBuffer> Mesh::CreateVertexBuffer(void* vertices, uint32_t size)
	{
		m_VertexBuffer = VertexBuffer::Create(vertices, size);
		return m_VertexBuffer;
	}


	Ref<IndexBuffer> Mesh::CreateIndexBuffer(uint32_t* indices, uint32_t count)
	{
		m_IndexBuffer = IndexBuffer::Create(indices, count);
		//m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		return m_IndexBuffer;
	}

	Ref<VertexArray> Mesh::GetVertexArray()
	{
		return m_VertexArray;
	}

	void Mesh::Bind()
	{
		
		
	}

	MATRIX4 Mesh::GetMatrix()
	{
		return transformMatrix;
	}

	MATRIX4 Mesh::GetDrawMatrix()
	{
		return drawMatrix;
	}

	void Mesh::SetMatrix(MATRIX4 transform)
	{
		transformMatrix = transform;
	}

	void Mesh::SetDrawMatrix(MATRIX4 transform)
	{
		drawMatrix = transform;
	}

	void Mesh::SetMaterial(Ref<Material> material)
	{
		m_material=material;
	}

	Ref<Material> Mesh::GetMaterial()
	{
		return m_material;
	}

	void Mesh::SetLayout(const BufferLayout& layout)
	{
		m_VertexBuffer->SetLayout(layout);
		//m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	}

	void Mesh::SetLayout(const BufferLayout& layout, Ref<Shader> shader)
	{
		m_VertexBuffer->SetLayout(layout, shader.get());
		//m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	}

	void Mesh::SetLayout(const BufferLayout& layout, Ref<Material> material)
	{
		m_material = material;
		m_VertexBuffer->SetLayout(layout, material->GetShader().get());
		//m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	}
	void Mesh::Draw()
	{

			
			m_material->ApplyMainTexture();
			m_material->ApplyLights();
			m_material->ApplySurface();
			Zorlock::Renderer::Submit(m_material->GetShader(), m_VertexArray, drawMatrix);


	}
	void Mesh::Destroy()
	{
		//need to create free mem commands in these classes
		//m_VertexArray->Release();
		//m_VertexBuffer->Release();
		//m_IndexBuffer->Release();
	}
	void Mesh::SetMeshID(uint32_t i)
	{
		m_meshID = i;
	}
	uint32_t Mesh::GetMeshID()
	{
		return m_meshID;
	}
}