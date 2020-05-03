#include "zMath.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

class Mesh
{
public:

	Mesh(DeviceContext* device_context,std::vector<Vertex> vertices,std::vector<DWORD> indices);
	Mesh(DeviceContext* device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices, std::vector<Texture> & textures);
	Mesh(DeviceContext* device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices, void * shader_byte_code, UINT size_byte_shader);
	Mesh(DeviceContext* device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices, std::vector<Texture> & textures, void * shader_byte_code, UINT size_byte_shader);
	Mesh(DeviceContext* device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices, std::vector<Texture> & textures, void * shader_byte_code, UINT size_byte_shader, const DirectX::XMMATRIX & transformMatrix);
	Mesh(DeviceContext* device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices, std::vector<Texture> & textures, const DirectX::XMMATRIX & transformMatrix);
	Mesh(DeviceContext* device_context, std::vector<Vertex> vertices, std::vector<DWORD> indices, void * shader_byte_code, UINT size_byte_shader, const DirectX::XMMATRIX & transformMatrix);
	const DirectX::XMMATRIX & GetTransformMatrix();
	void SetTextures(std::vector<Texture> & textures);
	void SetVertexLayout(void * shader_byte_code, UINT size_byte_shader);
	Mesh(const Mesh & mesh);
	void Release();
	void Draw();
	~Mesh();
private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	DeviceContext* m_device_context;
	std::vector<Texture> textures;
	DirectX::XMMATRIX transformMatrix;
	//VertexShader* m_vs;
	//PixelShader* m_ps;
};

