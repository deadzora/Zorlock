#include "BaseModel.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "ConstantPixelBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Math.h"
#include "StringConverter.h"


BaseModel::BaseModel()
{
}


BaseModel::~BaseModel()
{
}

bool BaseModel::init(DeviceContext * device_context)
{
	this->m_device_context = device_context;
	
	this->m_cb = GraphicsEngine::get()->create_constantbuffer<CB_VS_VertexShader3>();
	this->m_cb->setbufferindex(0);
	
	this->m_pcb = GraphicsEngine::get()->create_constantbuffer< CB_PS_PixelShader>();
	this->m_pcb->setbufferindex(1);
	
	this->a_pcb = GraphicsEngine::get()->create_constantbuffer< CB_PS_AmbientShader>();
	this->a_pcb->setbufferindex(2);
	
	this->l_pcb = GraphicsEngine::get()->create_constantbuffer< CB_PS_LIGHTS>();
	this->l_pcb->setbufferindex(3);

	this->m_cb->create();
	this->m_pcb->create();
	this->a_pcb->create();
	this->l_pcb->create();

	return true;
}

bool BaseModel::init(const std::string & filename, DeviceContext * device_context)
{
	this->m_device_context = device_context;
	this->m_cb = GraphicsEngine::get()->create_constantbuffer<CB_VS_VertexShader3>();
	this->m_cb->setbufferindex(0);

	this->m_pcb = GraphicsEngine::get()->create_constantbuffer< CB_PS_PixelShader>();
	this->m_pcb->setbufferindex(1);

	this->a_pcb = GraphicsEngine::get()->create_constantbuffer< CB_PS_AmbientShader>();
	this->a_pcb->setbufferindex(2);

	this->l_pcb = GraphicsEngine::get()->create_constantbuffer< CB_PS_LIGHTS>();
	this->l_pcb->setbufferindex(3);

	this->m_cb->create();
	this->m_pcb->create();
	this->a_pcb->create();
	this->l_pcb->create(true);



	return true;
}

void BaseModel::Draw(DirectX::XMMATRIX viewmatrix)
{
	assert("Override this method");
}

void BaseModel::Release()
{
	if (this->basetex)this->basetex->Release();
	this->m_cb->release();
	this->m_pcb->release();
	this->a_pcb->release();
	this->l_pcb->release();
	delete this;
}

bool BaseModel::LoadModel(const std::string & filename)
{
	assert("Override this method");
	return true;
}

void BaseModel::ApplyShaders()
{
	assert("Override this method");
}

void BaseModel::SetTexture(ID3D11ShaderResourceView * tex)
{
	assert("Override this method");
}

void BaseModel::SetTexture(Texture * tex)
{
	assert("Override this method");
}

bool BaseModel::LoadVertexShader(const wchar_t * filename)
{
	this->m_vs = new VertexShader();
	this->m_vs->init(filename);
	return true;
}

bool BaseModel::LoadPixelShader(const wchar_t * filename)
{
	this->m_ps = new PixelShader();
	this->m_ps->init(filename);
	return true;
}

void BaseModel::SetVertexShader(VertexShader * vs)
{
	this->m_vs = vs;
}

void BaseModel::SetPixelShader(PixelShader * ps)
{
	this->m_ps = ps;
}

ConstantBuffer<CB_PS_PixelShader> * BaseModel::GetConstantPixelBuffer()
{
	return this->m_pcb;
}

ConstantBuffer<CB_PS_AmbientShader>* BaseModel::GetConstantAmbientBuffer()
{
	return this->a_pcb;
}

ConstantBuffer<CB_PS_LIGHTS>* BaseModel::GetConstantLightBuffer()
{
	return this->l_pcb;
}
