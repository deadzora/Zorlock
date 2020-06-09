#pragma once
#include "Color.h"
#include "Zorlock/Game/GameObject.h"

namespace Zorlock {


	class Environment : public GameObject
	{
	public:
		Environment();
		~Environment();
		ColorRGBA GetAmbient();
		void SetAmbient(ColorRGBA col);

	protected:
		ColorRGBA m_ambient;
	};
	ZL_ENABLE_TYPENAME(Environment)
}