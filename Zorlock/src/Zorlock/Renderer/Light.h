#pragma once
#include "Zorlock/Game/GameObject.h"
#include "Zorlock/Renderer/Color.h"

namespace Zorlock {

	struct LightBase
	{
	public:
		LightBase() : lightpos(VECTOR4(0,0,0,1)), lightcolor(VECTOR4(1, 1, 1, 1)), radius(1.0f), strength(0.5f)
		{};
		VECTOR4 lightpos;
		VECTOR4 lightcolor;
		float radius;
		float strength;

		LightBase operator=(const LightBase& q) {
			lightpos = q.lightpos; lightcolor = q.lightcolor; radius = q.radius; strength = q.strength; return *this;
		}

	};

	class Light : public GameObject
	{
	public:
		Light();
		~Light();
		void SetRadius(float r);
		float GetRadius();
		void SetStrength(float s);
		float GetStrength();
		void SetColor(COLOR4 col);
		COLOR4 GetColor();
	private:
		LightBase m_lightProps;

	};



}