#include "ZLpch.h"
#include "Light.h"



namespace Zorlock {

	Light::Light(std::string name, Ref<Transform> parent) : GameObject(name,parent)
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

	void Light::SetColor(ColorRGBA col)
	{
		m_lightProps.lightcolor = col;
	}

	LightBase Light::GetLightProps()
	{
		return m_lightProps;
	}

	void Light::Update(Timestep ts)
	{
		GameObject::Update(ts);
		m_lightProps.lightpos =  transform->GetDrawMatrix().multiply(Vector4(transform->position,1));
	}

	ColorRGBA Light::GetColor()
	{
		return ColorRGBA(m_lightProps.lightcolor);
	}

	LightBase::LightBase() : lightpos(VECTOR4(0, 0, 0, 1)), lightcolor(VECTOR4(1, 1, 1, 1)), radius(1.0f), strength(0.5f)
	{}
	LightBase LightBase::operator=(const LightBase& q) {
		lightpos = q.lightpos; lightcolor = q.lightcolor; radius = q.radius; strength = q.strength; return *this;
	};



}
