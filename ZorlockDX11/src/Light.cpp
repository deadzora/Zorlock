#include "Light.h"
#include "GraphicsEngine.h"
#include "ErrorLogger.h"


Light::Light()
{
	this->init();
}

Light::Light(const wchar_t * vfilename, const wchar_t * pfilename)
{
	this->init("Data/Models/light.fbx", vfilename, pfilename);
}

bool Light::init(const std::string & filename, const wchar_t * vfilename, const wchar_t * pfilename)
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

	this->SetPosition(0.0f, 0.0f, 0.0f);
	this->SetRotation(0.0f, 0.0f, 0.0f);
	this->SetScale(1.0f, 1.0f, 1.0f);
	this->UpdateMatrix();


	return true;
}

bool Light::init(const std::string & filename)
{
	if (this->model) this->model->Release();
	this->model = new Model();
	if (!this->model->init(filename, GraphicsEngine::get()->getImmediateDeviceContext()))
	{
		ErrorLogger::Log("Failed to Initialize Model");
		return false;
	}

	this->SetPosition(0.0f, 0.0f, 0.0f);
	this->SetRotation(0.0f, 0.0f, 0.0f);
	this->SetScale(1.0f, 1.0f, 1.0f);
	this->UpdateMatrix();


	return true;
}

bool Light::init()
{
	if (this->model) this->model->Release();
	this->model = new Model();
	return true;
	if (!this->model->init("Data/Models/light.fbx" , GraphicsEngine::get()->getImmediateDeviceContext()))
	{
		ErrorLogger::Log("Failed to Initialize Model");
		return false;
	}
	this->SetPosition(0.0f, 0.0f, 0.0f);
	this->SetRotation(0.0f, 0.0f, 0.0f);
	this->SetScale(1.0f, 1.0f, 1.0f);
	this->UpdateMatrix();

}

void Light::SetLightColor(float r, float g, float b)
{
	this->lightcolor = DirectX::XMFLOAT3(r, g, b);
	/*
	if (this->model)
	{
		this->model->SetLightColor(r, g, b);
	}
	*/
}

void Light::SetLightBrightness(float b)
{
	this->lightStrength = b;
	/*
	if (this->model)
	{
		this->model->SetLightBrightness(b);
	}
	*/
}

void Light::SetLightAttenuation(float a, float b, float c)
{
	this->lightAttenuation_a = a;
	this->lightAttenuation_b = b;
	this->lightAttenuation_c = c;
}

void Light::SetLightRadius(float r)
{
	this->lightradius = r;
}

void Light::UpdateLight()
{
	//TBD
	/*
	if (this->model)
	{
		this->model->SetLightPosition(this->GetPositionFloat3());
	}
	*/
}

void Light::SetLightPosition(const XMFLOAT3 pos)
{
	//TBD
	/*
	if (this->model)
	{
		this->model->SetLightPosition(this->GetPositionFloat3());
	}
	*/
}

void Light::UpdateMatrix()
{

	this->m_world = DirectX::XMMatrixScaling(this->scale.x, this->scale.y, this->scale.z) * DirectX::XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z) * DirectX::XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
	this->UpdateDirectionVectors();

}


Light::~Light()
{
}
