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

	struct LightBase
	{
	public:
		LightBase();

		LightBase operator=(const LightBase& q);

		Vector4 lightpos;
		Vector4 lightcolor;
		float radius;
		float strength;
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
		virtual void Update(Timestep ts) override;
		ColorRGBA GetColor();
	private:
		LightBase m_lightProps;

	};



}

#define ZLLIGHT Zorlock::Light