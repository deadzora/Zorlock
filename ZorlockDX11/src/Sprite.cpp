#include "Sprite.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "zMath.h"

Sprite::Sprite()
{
}

bool Sprite::Init(float width, float height, const wchar_t * filename)
{
	this->texture = new Texture(filename, aiTextureType::aiTextureType_DIFFUSE);
	this->m_cb = GraphicsEngine::get()->create_constantbuffer<CB_VS_VertexShader3>();
	this->m_cb->create();
	this->m_device_context = GraphicsEngine::get()->getImmediateDeviceContext();
	Vertex vertexdata[] =
	{
		Vertex(-0.5f,-0.5f,0.0f,0.0f,0.0f,0.0f),
		Vertex(0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f),
		Vertex(-0.5f,0.5f,0.0f,0.0f,1.0f,0.0f),
		Vertex(0.5f,0.5f,0.0f,1.0f,1.0f,0.0f)
	};

	DWORD indexdata[] = 
	{
		0,1,2,
		2,1,3
	};

	this->m_vb = GraphicsEngine::get()->create_vertexbuffer();
	UINT size_list = ARRAYSIZE(vertexdata);

	this->m_ib = GraphicsEngine::get()->create_indexbuffer();
	UINT indexsize_list = ARRAYSIZE(indexdata);


	this->LoadVertexShader(L"shader2d.fx");
	this->LoadPixelShader(L"shader2d.fx");

	this->m_vb->load(vertexdata, sizeof(Vertex), size_list, this->m_vs->GetBuffer()->GetBufferPointer(), this->m_vs->GetBuffer()->GetBufferSize());
	this->m_ib->load(indexdata, sizeof(DWORD), indexsize_list);

	this->SetPosition(0, 0, 1);
	this->SetRotation(0, 0, 0);
	this->SetScale(width, height, 1);
	this->UpdateMatrix();
	return true;
}

void Sprite::Draw(XMMATRIX orthomatrix)
{
	this->UpdateMatrix();
	XMMATRIX wvpMatrix = this->m_world * orthomatrix;
	this->m_cb->setmatrix(wvpMatrix, this->m_world);
	this->m_cb->apply();
	this->m_device_context->setvertexshader(this->m_vs);
	this->m_device_context->setpixelshader(this->m_ps);
	//this->m_device_context->setblendstate();
	this->m_device_context->setshadertexture(this->texture->GetTexture());
	this->m_device_context->setvertexbuffer(this->m_vb);
	this->m_device_context->setindexbuffer(this->m_ib);
	this->m_device_context->drawIndexed(this->m_ib->GetIndexListSize(), 0, 0);
	//this->m_cb->setalpha(1.0f);
}

float Sprite::GetWidth()
{
	return this->scale.x;
}

float Sprite::GetHeight()
{
	return this->scale.y;
}

bool Sprite::LoadVertexShader(const wchar_t * filename)
{
	this->m_vs = new VertexShader();
	this->m_vs->init(filename);
	return true;
}

bool Sprite::LoadPixelShader(const wchar_t * filename)
{
	this->m_ps = new PixelShader();
	this->m_ps->init(filename);
	return true;
}

void Sprite::SetVertexShader(VertexShader * vs)
{
	this->m_vs = vs;
}

void Sprite::SetPixelShader(PixelShader * ps)
{
	this->m_ps = ps;
}

void Sprite::Release()
{
	//add texture release
	if (this->m_cb)this->m_cb->release();
	if (this->m_ib)this->m_ib->release();
	if (this->m_vb)this->m_vb->release();
	if (this->m_vs)this->m_vs->release();
	if (this->m_ps)this->m_ps->release();
	delete this;
}


Sprite::~Sprite()
{
	this->Release();
}

void Sprite::UpdateMatrix()
{
	this->m_world = XMMatrixScaling(this->scale.x, this->scale.y, 1.0f) * XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z) * XMMatrixTranslation(this->pos.x + (this->scale.x / 2.0f), this->pos.y + (this->scale.y / 2.0f), this->pos.z);
}
