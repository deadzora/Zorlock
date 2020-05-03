#pragma once
#include "Object2D.h"
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"

class Sprite : public Object2D
{
public:
	Sprite();
	bool Init(float width, float height, const wchar_t * filename);
	void Draw(XMMATRIX orthomatrix);
	float GetWidth();
	float GetHeight();
	bool LoadVertexShader(const wchar_t * filename);
	bool LoadPixelShader(const wchar_t * filename);
	void SetVertexShader(VertexShader* vs);
	void SetPixelShader(PixelShader* ps);
	void Release();
	~Sprite();
private:
	void UpdateMatrix() override;
	DeviceContext* m_device_context;
	Texture* texture;
	ConstantBuffer<CB_VS_VertexShader3> * m_cb;
	IndexBuffer * m_ib;
	VertexBuffer * m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
};

