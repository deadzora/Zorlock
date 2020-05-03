#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

constexpr auto MAXNUMLIGHTS = 16;

struct CB_Shader
{
	CB_Shader() {};
	~CB_Shader() {};
};

struct CB_VS_VertexShader : public CB_Shader
{
	DirectX::XMMATRIX wpvMatrix;
};

struct CB_VS_VertexShader3 : public CB_VS_VertexShader
{
	DirectX::XMMATRIX worldMatrix;
};



struct CB_PS_PixelShader : public CB_Shader
{
	float alpha = 1.0f;

};

struct CB_PS_AmbientShader : public CB_Shader
{
	float lightstrength = 1.0f;
	DirectX::XMFLOAT3 lightcolor = { 0.5, 0.5, 0.5 };
};

struct LightBase
{
	DirectX::XMFLOAT3 lightpos; 
	float radius;
	DirectX::XMFLOAT3 lightcolor;
	float strength;
};

struct CB_PS_LIGHTS : public CB_Shader
{
	LightBase lights[MAXNUMLIGHTS];

};
