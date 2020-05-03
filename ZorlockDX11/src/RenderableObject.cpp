#include "RenderableObject.h"
#include "GraphicsEngine.h"
#include "ErrorLogger.h"


RenderableObject::RenderableObject()
{
	this->init();
}

RenderableObject::RenderableObject(const std::string & filename)
{
	this->init(filename);
}

RenderableObject::RenderableObject(const std::string & filename, const wchar_t * vfilename, const wchar_t * pfilename)
{
	this->init(filename, vfilename, pfilename);
}

void RenderableObject::SetTexture(Texture * tex)
{
	this->model->SetTexture(tex);
}

void RenderableObject::SetTexture(ID3D11ShaderResourceView * tex)
{
	this->model->SetTexture(tex);
}

bool RenderableObject::LoadVertexShader(const wchar_t * filename)
{
	return this->model->LoadVertexShader(filename);
}

bool RenderableObject::LoadPixelShader(const wchar_t * filename)
{
	return this->model->LoadPixelShader(filename);
}

void RenderableObject::SetVertexShader(VertexShader * vs)
{
	this->model->SetVertexShader(vs);
}

void RenderableObject::SetPixelShader(PixelShader * ps)
{
	this->model->SetPixelShader(ps);
}

ConstantBuffer<CB_PS_PixelShader> * RenderableObject::GetConstantPixelBuffer()
{
	if (this->model)
	{
		return this->model->GetConstantPixelBuffer();
	}
	else {
		return nullptr;
	}
}

ConstantBuffer<CB_PS_AmbientShader>* RenderableObject::GetConstantAmbientBuffer()
{
	if (this->model)
	{
		return this->model->GetConstantAmbientBuffer();
	}
	else {
		return nullptr;
	}
}

ConstantBuffer<CB_PS_LIGHTS>* RenderableObject::GetConstantLightBuffer()
{
	if (this->model)
	{
		return this->model->GetConstantLightBuffer();
	}
	else {
		return nullptr;
	}
}

void RenderableObject::Draw(DirectX::XMMATRIX viewmatrix)
{
	this->UpdateMatrix();
	this->model->Draw(this->m_world*viewmatrix);
}


RenderableObject::~RenderableObject()
{
}

bool RenderableObject::init()
{
	if (this->model) this->model->Release();
	this->model = new Model();

	if (!this->model->init(GraphicsEngine::get()->getImmediateDeviceContext()))
	{
		ErrorLogger::Log("Failed to Initialize Empty Model");
		return false;
	}
	this->SetScale(1.0f, 1.0f, 1.0f);

	this->UpdateMatrix();
	return true;
}

bool RenderableObject::init(const std::string & filename)
{
	if (this->model) this->model->Release();


		this->model = new Model();


	

	if (!this->model->init(filename, GraphicsEngine::get()->getImmediateDeviceContext()))
	{
		ErrorLogger::Log("Failed to Initialize Model");
		return false;
	}
	this->scale = XMFLOAT3(1, 1, 1);
	this->UpdateMatrix();
	return true;
}

bool RenderableObject::init(const std::string & filename, const wchar_t * vfilename, const wchar_t * pfilename)
{
	if (this->model) this->model->Release();
	this->model = new Model();
	this->model->LoadVertexShader(vfilename);
	this->model->LoadPixelShader(pfilename);
	if (!this->model->init(filename, GraphicsEngine::get()->getImmediateDeviceContext()))
	{
		ErrorLogger::Log("Failed to Initialize Model");
		return false;
	}
	this->scale = XMFLOAT3(1, 1, 1);
	this->UpdateMatrix();
	return true;
}

void RenderableObject::Release()
{
	this->model->Release();
	delete this;
}

void RenderableObject::UpdateMatrix()
{
	this->m_world = DirectX::XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z)*DirectX::XMMatrixScaling(this->scale.x, this->scale.y, this->scale.z) * DirectX::XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	this->UpdateDirectionVectors();
}

