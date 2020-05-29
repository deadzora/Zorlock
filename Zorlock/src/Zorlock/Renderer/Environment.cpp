#include "ZLpch.h"
#include "Environment.h"

namespace Zorlock {



	Environment::Environment() : m_ambient(ColorRGBA::HALF())
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
