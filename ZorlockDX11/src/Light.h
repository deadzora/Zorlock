#pragma once
#include "RenderableObject.h"
class Light : public RenderableObject
{
public:
	Light();
	Light(const wchar_t * vfilename, const wchar_t * pfilename);
	bool init(const std::string & filename, const wchar_t * vfilename, const wchar_t * pfilename) override;
	bool init(const std::string & filename) override;
	bool init() override;
	void SetLightColor(float r, float g, float b);
	void SetLightBrightness(float b);
	void SetLightAttenuation(float a, float b, float c);
	void SetLightRadius(float r);
	void UpdateLight();
	void SetLightPosition(const XMFLOAT3 pos);
	void UpdateMatrix() override;
	DirectX::XMFLOAT3 lightcolor = {1.0f,1.0f,1.0f};
	float lightStrength = 1.0f;
	float lightAttenuation_a = 1.0f;
	float lightAttenuation_b = 0.25f;
	float lightAttenuation_c = 0.1f;
	float lightradius = 500.0f;
	~Light();
};

