#pragma once
#include "ConstantBuffer.h"
#include <d3d11.h>
#include <DirectXMath.h>

//Depreciated, now using templates


/*
class ConstantPixelBuffer :
	public ConstantBuffer
{
public:
	virtual bool create() override;
	virtual bool release() override;
	virtual bool apply() override;
	void setalpha(float a);
	void setlightcolor(int lightnum, float r, float g, float b);
	void setlightbright(int lightnum, float b);
	void setlightpos(int lightnum, const DirectX::XMFLOAT3 & pos);
	void setlightattenuation(int lightnum, float a, float b, float c);
	void setlightradius(int lightnum, float radius);
	ConstantPixelBuffer();
	ConstantPixelBuffer(ID3D11DeviceContext* device_context, ID3D11Device* d3d_device);
	~ConstantPixelBuffer();
protected:

	CB_PS_PixelShader* m_psd;
	CB_PS_AmbientShader* m_asd;
	CB_PS_LIGHTS* m_lsd;
	ID3D11Buffer* m_abuffer;
	ID3D11Buffer* m_lsbuffer;
};
*/

