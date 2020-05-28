#include "ZLpch.h"
#include "Light.h"


namespace Zorlock {

	Light::Light()
	{

	}

	Light::~Light()
	{
	}

	void Light::SetRadius(float r)
	{
		m_lightProps.radius = r;
	}

	float Light::GetRadius()
	{
		return m_lightProps.radius;
	}

	void Light::SetStrength(float s)
	{
		m_lightProps.strength = s;
	}

	float Light::GetStrength()
	{
		return m_lightProps.strength;
	}

	void Light::SetColor(COLOR4 col)
	{
		m_lightProps.lightcolor = col;
	}

	COLOR4 Light::GetColor()
	{
		return COLOR4(m_lightProps.lightcolor);
	}

}
