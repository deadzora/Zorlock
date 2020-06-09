#include "ZLpch.h"
#include "Environment.h"

namespace Zorlock {



	Environment::Environment() : GameObject("Environment",nullptr), m_ambient(ColorRGBA::BLACK())
	{
		type = ZL_GETTYPENAME(Environment)
	}

	Environment::~Environment()
	{
	}

	ColorRGBA Environment::GetAmbient()
	{
		return m_ambient;
	}

	void Environment::SetAmbient(ColorRGBA col)
	{
		m_ambient = col;
	}


}
