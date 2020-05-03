#pragma once
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "Mesh.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>

using namespace DirectX;

class BaseModel
{
public:
	BaseModel();
	~BaseModel();
	virtual bool init(DeviceContext* device_context);
	virtual bool init(const std::string & filename, DeviceContext* device_context);
	virtual void Draw(DirectX::XMMATRIX viewmatrix);
	virtual void Release();
	virtual bool LoadModel(const std::string & filename);
	virtual void ApplyShaders();
	virtual void SetTexture(ID3D11ShaderResourceView* tex);
	virtual void SetTexture(Texture * tex);
	virtual void Update() {};
	bool LoadVertexShader(const wchar_t * filename);
	bool LoadPixelShader(const wchar_t * filename);
	void SetVertexShader(VertexShader* vs);
	void SetPixelShader(PixelShader* ps);
	ConstantBuffer<CB_PS_PixelShader> * GetConstantPixelBuffer();
	ConstantBuffer<CB_PS_AmbientShader> * GetConstantAmbientBuffer();
	ConstantBuffer<CB_PS_LIGHTS> * GetConstantLightBuffer();

protected:
	float alpha = 1.0f;
	float m_scale = 1.0f;
	std::string directory = "";
	ID3D11ShaderResourceView* basetex;
	DeviceContext* m_device_context;
	ConstantBuffer<CB_VS_VertexShader3>* m_cb;
	ConstantBuffer<CB_PS_PixelShader>* m_pcb;
	ConstantBuffer<CB_PS_AmbientShader>* a_pcb;
	ConstantBuffer<CB_PS_LIGHTS>* l_pcb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	std::vector<Mesh> meshes;
};

