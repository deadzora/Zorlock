#include "ZLpch.h"
#include "Environment.h"

namespace Zorlock {



	Environment::Environment() : m_ambient(ColorRGBA::BLACK())
	{

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
