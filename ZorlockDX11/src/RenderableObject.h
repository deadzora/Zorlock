#pragma once
#include "GameObject.h"
#include "Object3D.h"
#include "BaseModel.h"
#include "Model.h"

class RenderableObject : public Object3D
{
public:
	RenderableObject();
	RenderableObject(const std::string & filename);
	RenderableObject(const std::string & filename, const wchar_t * vfilename, const wchar_t * pfilename);
	void SetTexture(Texture* tex);
	void SetTexture(ID3D11ShaderResourceView* tex);
	bool LoadVertexShader(const wchar_t * filename);
	bool LoadPixelShader(const wchar_t * filename);
	void SetVertexShader(VertexShader* vs);
	void SetPixelShader(PixelShader* ps);
	ConstantBuffer<CB_PS_PixelShader> * GetConstantPixelBuffer();
	ConstantBuffer<CB_PS_AmbientShader>* GetConstantAmbientBuffer();
	ConstantBuffer<CB_PS_LIGHTS>* GetConstantLightBuffer();


	void Draw(DirectX::XMMATRIX viewmatrix);
	virtual bool init();
	virtual bool init(const std::string & filename);
	virtual bool init(const std::string & filename, const wchar_t * vfilename, const wchar_t * pfilename);
	void Release();
	~RenderableObject();
protected:
	void UpdateMatrix() override;
	BaseModel* model;
	float alpha = 1.0f;
	
};

