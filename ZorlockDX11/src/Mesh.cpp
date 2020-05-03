#include "Mesh.h"
#include "Math.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "ErrorLogger.h"
#include <vector>



Mesh::Mesh(DeviceContext * device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices)
{
	this->m_device_context = device_context;

	this->m_vb = GraphicsEngine::get()->create_vertexbuffer();
	this->m_ib = GraphicsEngine::get()->create_indexbuffer();
	if (!this->m_vb->load(vertices.data(), sizeof(Vertex), vertices.size()))
	{
		ErrorLogger::Log("Failed to Load Vertices");
	}
	if (!this->m_ib->load(indices.data(), sizeof(DWORD), indices.size()))
	{
		ErrorLogger::Log("Failed to Load Indices");
	}
}

Mesh::Mesh(DeviceContext * device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices, std::vector<Texture>& textures)
{
	
	this->m_device_context = device_context;
	this->textures = textures;
	this->m_vb = GraphicsEngine::get()->create_vertexbuffer();
	this->m_ib = GraphicsEngine::get()->create_indexbuffer();
	if (!this->m_vb->load(vertices.data(), sizeof(Vertex), vertices.size()))
	{
		ErrorLogger::Log("Failed to Load Vertices");
	}
	if (!this->m_ib->load(indices.data(), sizeof(DWORD), indices.size()))
	{
		ErrorLogger::Log("Failed to Load Indices");
	}
}

Mesh::Mesh(DeviceContext * device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices, void * shader_byte_code, UINT size_byte_shader)
{
	this->m_device_context = device_context;

	this->m_vb = GraphicsEngine::get()->create_vertexbuffer();
	this->m_ib = GraphicsEngine::get()->create_indexbuffer();
	
	if (!this->m_vb->load(vertices.data(), sizeof(Vertex), vertices.size()))
	{
		ErrorLogger::Log("Failed to Load Vertices");
	}
	this->m_vb->setlayout(shader_byte_code, size_byte_shader);
	if (!this->m_ib->load(indices.data(), sizeof(DWORD), indices.size()))
	{
		ErrorLogger::Log("Failed to Load Indices");
	}
}

Mesh::Mesh(DeviceContext * device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices, std::vector<Texture>& textures, void * shader_byte_code, UINT size_byte_shader)
{
	this->m_device_context = device_context;
	this->textures = textures;
	this->m_vb = GraphicsEngine::get()->create_vertexbuffer();
	this->m_ib = GraphicsEngine::get()->create_indexbuffer();

	if (!this->m_vb->load(vertices.data(), sizeof(Vertex), vertices.size()))
	{
		ErrorLogger::Log("Failed to Load Vertices");
	}
	this->m_vb->setlayout(shader_byte_code, size_byte_shader);
	if (!this->m_ib->load(indices.data(), sizeof(DWORD), indices.size()))
	{
		ErrorLogger::Log("Failed to Load Indices");
	}
}

Mesh::Mesh(DeviceContext * device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices, std::vector<Texture>& textures, void * shader_byte_code, UINT size_byte_shader, const DirectX::XMMATRIX & transformMatrix)
{
	this->m_device_context = device_context;
	this->textures = textures;
	this->m_vb = GraphicsEngine::get()->create_vertexbuffer();
	this->m_ib = GraphicsEngine::get()->create_indexbuffer();
	this->transformMatrix = transformMatrix;
	if (!this->m_vb->load(vertices.data(), sizeof(Vertex), vertices.size()))
	{
		ErrorLogger::Log("Failed to Load Vertices");
	}
	this->m_vb->setlayout(shader_byte_code, size_byte_shader);
	if (!this->m_ib->load(indices.data(), sizeof(DWORD), indices.size()))
	{
		ErrorLogger::Log("Failed to Load Indices");
	}
}

Mesh::Mesh(DeviceContext * device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices, std::vector<Texture>& textures, const DirectX::XMMATRIX & transformMatrix)
{
	this->m_device_context = device_context;
	this->textures = textures;
	this->m_vb = GraphicsEngine::get()->create_vertexbuffer();
	this->m_ib = GraphicsEngine::get()->create_indexbuffer();
	this->transformMatrix = transformMatrix;
	if (!this->m_vb->load(vertices.data(), sizeof(Vertex), vertices.size()))
	{
		ErrorLogger::Log("Failed to Load Vertices");
	}
	if (!this->m_ib->load(indices.data(), sizeof(DWORD), indices.size()))
	{
		ErrorLogger::Log("Failed to Load Indices");
	}
}

Mesh::Mesh(DeviceContext * device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices, void * shader_byte_code, UINT size_byte_shader, const DirectX::XMMATRIX & transformMatrix)
{
	this->m_device_context = device_context;
	this->textures = textures;
	this->m_vb = GraphicsEngine::get()->create_vertexbuffer();
	this->m_ib = GraphicsEngine::get()->create_indexbuffer();
	this->transformMatrix = transformMatrix;
	if (!this->m_vb->load(vertices.data(), sizeof(Vertex), vertices.size()))
	{
		ErrorLogger::Log("Failed to Load Vertices");
	}
	this->m_vb->setlayout(shader_byte_code, size_byte_shader);
	if (!this->m_ib->load(indices.data(), sizeof(DWORD), indices.size()))
	{
		ErrorLogger::Log("Failed to Load Indices");
	}
}

const DirectX::XMMATRIX & Mesh::GetTransformMatrix()
{
	return this->transformMatrix;
}

void Mesh::SetTextures(std::vector<Texture>& textures)
{
	this->textures = textures;
}

void Mesh::SetVertexLayout(void * shader_byte_code, UINT size_byte_shader)
{
	this->m_vb->setlayout(shader_byte_code, size_byte_shader);
}

Mesh::Mesh(const Mesh & mesh)
{
	this->m_device_context = mesh.m_device_context;
	this->m_ib = mesh.m_ib;
	this->m_vb = mesh.m_vb;
	this->textures = mesh.textures;
	this->transformMatrix = mesh.transformMatrix;
}

void Mesh::Release()
{
	if (this->m_vb)this->m_vb->release();
	if (this->m_ib)this->m_ib->release();

}

void Mesh::Draw()
{
	for (int i = 0; i < this->textures.size(); i++)
	{
		if (this->textures[i].GetType() == aiTextureType::aiTextureType_DIFFUSE)
		{
			this->m_device_context->setshadertexture(this->textures[i].GetTexture());
			break;
		}
	}

	this->m_device_context->setvertexbuffer(this->m_vb);
	this->m_device_context->setindexbuffer(this->m_ib);
	this->m_device_context->drawIndexed(this->m_ib->GetIndexListSize(), 0, 0);
}

Mesh::~Mesh()
{
}
