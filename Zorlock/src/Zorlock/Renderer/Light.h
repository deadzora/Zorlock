#pragma once
#include "Zorlock/Game/GameObject.h"
#include "Zorlock/Core/Math.h"
#include "Zorlock/Renderer/Color.h"

namespace Zorlock {

	enum class LightType
	{
		POINTLIGHT = 0,
		SPOTLIGHT = 1,
		DIRECTIONAL = 2
	};

	__declspec(align(16)) struct LightBase
	{
	public:
		LightBase();

		LightBase operator=(const LightBase& q);
		bool operator==(const LightBase& q);
		Vector4 lightpos;
		Vector4 lightcolor;
		float radius;
		float strength;
		//float specular;
		//float shininess;
	};

	class Light : public GameObject
	{
	public:
		Light(std::string name = "Light", Ref<Transform> parent = nullptr);
		~Light();
		void SetRadius(float r);
		float GetRadius();
		void SetStrength(float s);
		float GetStrength();
		void SetColor(ColorRGBA col);
		LightBase GetLightProps();		
		ColorRGBA GetColor();
		virtual void Update(Timestep ts) override;
	private:
		LightBase m_lightProps;

	};


	ZL_ENABLE_TYPENAME(Light)
}

#define ZLLIGHT Zorlock::Light