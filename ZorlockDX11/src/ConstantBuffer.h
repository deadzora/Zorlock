#pragma once
#include "ConstantBufferTypes.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include "ErrorLogger.h"

class DeviceContext;

template <class T>
class ConstantBuffer
{
public:
	ConstantBuffer(ID3D11DeviceContext* device_context, ID3D11Device* d3d_device) : m_device_context(device_context), m_d3d_device(d3d_device){};
	ConstantBuffer() {
		m_device_context = GraphicsEngine::get()->m_imm_context;
		m_d3d_device = GraphicsEngine::get()->m_d3d_device;
	};
	bool create()
	{
		{
			if (m_buffer)m_buffer->Release();


			D3D11_BUFFER_DESC buff_desc = {};
			buff_desc.Usage = D3D11_USAGE_DYNAMIC;
			buff_desc.ByteWidth = sizeof(T) + (16 - (sizeof(T) % 16));
			buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			buff_desc.MiscFlags = 0;
			buff_desc.StructureByteStride = 0;

			//D3D11_SUBRESOURCE_DATA init_data = {};
			//init_data.pSysMem = list_constants;

			//m_size_constant = size_constant;

			this->m_vsd = new T;
			HRESULT hr = GraphicsEngine::get()->Get3dDevice()->CreateBuffer(&buff_desc, 0, &this->m_buffer);
			if (FAILED(hr))
			{
				ErrorLogger::log(hr, "Failed to Create Constant Buffer");
				return false;
			}



			return true;
		}
	};

	bool create(bool nb)
	{
		if (m_buffer)m_buffer->Release();


		D3D11_BUFFER_DESC buff_desc = {};

		buff_desc.Usage = D3D11_USAGE_DYNAMIC;
		if (nb)
		{
			buff_desc.ByteWidth = sizeof(T);
		}
		else {
			buff_desc.ByteWidth = sizeof(T) + (16 - (sizeof(T) % 16));
		}
		buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		buff_desc.MiscFlags = 0;
		buff_desc.StructureByteStride = 0;

		//D3D11_SUBRESOURCE_DATA init_data = {};
		//init_data.pSysMem = list_constants;

		//m_size_constant = size_constant;

		this->m_vsd = new T;
		HRESULT hr = GraphicsEngine::get()->Get3dDevice()->CreateBuffer(&buff_desc, 0, &this->m_buffer);
		if (FAILED(hr))
		{
			ErrorLogger::log(hr, "Failed to Create Constant Buffer");
			return false;
		}



		return true;
	};

	bool release()
	{
		if (this->m_buffer)this->m_buffer->Release();
		delete this->m_vsd;
		delete this;
		return true;
	};

	bool apply()
	{
		if (!this->m_buffer)
		{
			ErrorLogger::Log("ConstantBuffer Buffer Pointer was Null");
			return false;
		}

		D3D11_MAPPED_SUBRESOURCE init_data = {};
		//ZeroMemory(&init_data, sizeof(D3D11_MAPPED_SUBRESOURCE));
		HRESULT hr;
		hr = this->m_device_context->Map(this->m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
		if (FAILED(hr))
		{
			ErrorLogger::log(hr, "Could not Map Initial Data");
			return false;
		}
		//find a way to pass struct types

		
		CopyMemory(init_data.pData, this->m_vsd, sizeof(T));
		

		this->m_device_context->Unmap(this->m_buffer, 0);
		this->m_device_context->VSSetConstantBuffers(this->bufferindex, 1, &this->m_buffer);
		return true;
	};



	bool applyps()
	{
		if (!this->m_buffer)
		{
			ErrorLogger::Log("ConstantBuffer Buffer Pointer was Null");
			return false;
		}

		D3D11_MAPPED_SUBRESOURCE init_data = {};
		//ZeroMemory(&init_data, sizeof(D3D11_MAPPED_SUBRESOURCE));
		HRESULT hr;
		hr = this->m_device_context->Map(this->m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
		if (FAILED(hr))
		{
			ErrorLogger::log(hr, "Could not Map Initial Data");
			return false;
		}
		//find a way to pass struct types


		CopyMemory(init_data.pData, this->m_vsd, sizeof(T));


		this->m_device_context->Unmap(this->m_buffer, 0);
		this->m_device_context->PSSetConstantBuffers(this->bufferindex, 1, &this->m_buffer);
		return true;
	};

	bool applycs()
	{
		if (!this->m_buffer)
		{
			ErrorLogger::Log("ConstantBuffer Buffer Pointer was Null");
			return false;
		}

		D3D11_MAPPED_SUBRESOURCE init_data = {};
		//ZeroMemory(&init_data, sizeof(D3D11_MAPPED_SUBRESOURCE));
		HRESULT hr;
		hr = this->m_device_context->Map(this->m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
		if (FAILED(hr))
		{
			ErrorLogger::log(hr, "Could not Map Initial Data");
			return false;
		}
		//find a way to pass struct types


		CopyMemory(init_data.pData, this->m_vsd, sizeof(T));


		this->m_device_context->Unmap(this->m_buffer, 0);
		this->m_device_context->CSSetConstantBuffers(this->bufferindex, 1, &this->m_buffer);
		return true;
	};


	bool settranslate(float x, float y, float z)
	{
		//CB_VS_VertexShader * mvsd = const_cast<CB_VS_VertexShader*>(reinterpret_cast<const CB_VS_VertexShader*>(&this->m_vsd));
		//if (mvsd)
		//{
		this->m_vsd->wpvMatrix = DirectX::XMMatrixTranslation(x, y, z);
		this->m_vsd->wpvMatrix = DirectX::XMMatrixTranspose(this->m_vsd->wpvMatrix);
			//this->m_vsd = mvsd;
			return true;
		//}
		//return true;
	};

	bool setrotation(float roll, float pitch, float yaw)
	{
		{
			//CB_VS_VertexShader * mvsd = const_cast<CB_VS_VertexShader*>(reinterpret_cast<const CB_VS_VertexShader*>(&this->m_vsd));
			//if (mvsd)
			//{
			this->m_vsd->wpvMatrix = DirectX::XMMatrixRotationRollPitchYaw(Math::RadiansFromDegrees(roll), Math::RadiansFromDegrees(pitch), Math::RadiansFromDegrees(yaw));
			this->m_vsd->wpvMatrix = DirectX::XMMatrixTranspose(this->m_vsd->wpvMatrix);
				//this->m_vsd = mvsd;
				return true;
			//}
			//return true;
		}
	};

	bool setscale(float x, float y, float z)
	{
		//CB_VS_VertexShader * mvsd = const_cast<CB_VS_VertexShader*>(reinterpret_cast<const CB_VS_VertexShader*>(&this->m_vsd));
		//if (mvsd)
		//{
		this->m_vsd->wpvMatrix = DirectX::XMMatrixScaling(x, y, z);
		this->m_vsd->wpvMatrix = DirectX::XMMatrixTranspose(this->m_vsd->wpvMatrix);
			//this->m_vsd = mvsd;
			return true;
		//}
		//return true;
	};

	bool setmatrix(DirectX::XMMATRIX matrix)
	{
		//CB_VS_VertexShader * mvsd = const_cast<CB_VS_VertexShader*>(reinterpret_cast<const CB_VS_VertexShader*>(&this->m_vsd));
		//if (mvsd)
		//{
		this->m_vsd->wpvMatrix = matrix;
		this->m_vsd->wpvMatrix = DirectX::XMMatrixTranspose(this->m_vsd->wpvMatrix);
			//this->m_vsd = mvsd;
			return true;
		//}
		//return true;
	};

	bool setmatrix(DirectX::XMMATRIX matrix, DirectX::XMMATRIX wmatrix)
	{
		//CB_VS_VertexShader3 * mvsd = const_cast<CB_VS_VertexShader3*>(reinterpret_cast<const CB_VS_VertexShader3*>(&this->m_vsd));
		//if (mvsd)
		//{
		this->m_vsd->wpvMatrix = matrix;
		this->m_vsd->worldMatrix = wmatrix;
		this->m_vsd->wpvMatrix = DirectX::XMMatrixTranspose(this->m_vsd->wpvMatrix);
		this->m_vsd->worldMatrix = DirectX::XMMatrixTranspose(this->m_vsd->worldMatrix);
			//this->m_vsd = mvsd;

			return true;
		//}

		//return false;
	};

	//If pixel buffer
	void setalpha(float a)
	{
		//CB_PS_PixelShader * mvsd = const_cast<CB_PS_PixelShader*>(reinterpret_cast<const CB_PS_PixelShader*>(&this->m_vsd));
		//if (mvsd)
		//{
			this->m_vsd->alpha = a;
			//this->m_vsd = mvsd;
		//}
	};
	void setlightcolor(int lightnum, float r, float g, float b)
	{
		//CB_PS_LIGHTS * mvsd = const_cast<CB_PS_LIGHTS*>(reinterpret_cast<const CB_PS_LIGHTS*>(&this->m_vsd));
		//if (mvsd)
		//{
		this->m_vsd->lights[lightnum].lightcolor = { r,g,b };
			//this->m_vsd = mvsd;
		//}
	};

	void setlightbright(int lightnum, float b)
	{
		//CB_PS_LIGHTS * mvsd = const_cast<CB_PS_LIGHTS*>(reinterpret_cast<const CB_PS_LIGHTS*>(&this->m_vsd));
		//if (mvsd)
		//{
		this->m_vsd->lights[lightnum].strength = b;
			//this->m_vsd = mvsd;
		//}
	};
	void setlightpos(int lightnum, const DirectX::XMFLOAT3 & pos)
	{
		//CB_PS_LIGHTS * mvsd = const_cast<CB_PS_LIGHTS*>(reinterpret_cast<const CB_PS_LIGHTS*>(&this->m_vsd));
		//if (mvsd)
		//{
		this->m_vsd->lights[lightnum].lightpos = pos;
			//this->m_vsd = mvsd;
		//}
	};
	void setlightattenuation(int lightnum, float a, float b, float c)
	{
		//hard code these values for now
		//this->m_asd->dynamiclightattenuation_a[lightnum] = a;
		//this->m_asd->dynamiclightattenuation_b[lightnum] = b;
		//this->m_asd->dynamiclightattenuation_c[lightnum] = c;
	};
	void setlightradius(int lightnum, float radius)
	{
		//CB_PS_LIGHTS * mvsd = const_cast<CB_PS_LIGHTS*>(reinterpret_cast<const CB_PS_LIGHTS*>(&this->m_vsd));
		//if (mvsd)
		//{
		this->m_vsd->lights[lightnum].radius = radius;
			//this->m_vsd = mvsd;
		//}
	};

	void setbufferindex(int i)
	{
		this->bufferindex = i;
	};

	int getbufferindex()
	{
		return bufferindex;
	};

	~ConstantBuffer() {};
protected:
	int bufferindex;
	ID3D11DeviceContext* m_device_context;
	ID3D11Device* m_d3d_device;
	//UINT m_size_constant;
	ID3D11Buffer* m_buffer;
	T* m_vsd;
	friend class DeviceContext;
};


