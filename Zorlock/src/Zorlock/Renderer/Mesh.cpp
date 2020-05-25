#include "ZLpch.h"
#include "Mesh.h"
#include "Zorlock/Renderer/Renderer.h"


namespace Zorlock
{
	Mesh::Mesh() : drawMatrix(MATRIX4::IDENTITY()), transformMatrix(MATRIX4::IDENTITY())
	{
	}
	void Mesh::CreateVertexArray()
	{
		m_VertexArray = VertexArray::Create();

	}

	void Mesh::CreateVertexBuffer(float* vertices, uint32_t size)
	{
		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
	}

	void Mesh::CreateVertexBuffer(Vertex* vertices, uint32_t size)
	{
		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
	}

	void Mesh::CreateVertexBuffer(void* vertices, uint32_t size)
	{
		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
	}


	void Mesh::CreateIndexBuffer(uint32_t* indices, uint32_t count)
	{
		m_IndexBuffer = IndexBuffer::Create(indices, count);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
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

	void Mesh::SetLayout(const BufferLayout& layout)
	{
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	}

	void Mesh::SetLayout(const BufferLayout& layout, Ref<Shader> shader)
	{
		m_VertexBuffer->SetLayout(layout, shader.get());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	}

	void Mesh::SetLayout(const BufferLayout& layout, Ref<Material> material)
	{
		m_material = material;
		m_VertexBuffer->SetLayout(layout, material->GetShader().get());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	}
	void Mesh::Draw()
	{

			m_material->GetShader()->Bind();			
			m_material->ApplyMainTexture();
			m_material->ApplyViewMatrix();
			m_material->ApplyTransform(drawMatrix);		
			m_material->GetShader()->Apply();
			m_VertexArray->Bind();
			RenderCommand::DrawIndexed(m_VertexArray);

	}
	void Mesh::Destroy()
	{
		//need to create free mem commands in these classes
		//m_VertexArray->Release();
		//m_VertexBuffer->Release();
		//m_IndexBuffer->Release();
	}
}