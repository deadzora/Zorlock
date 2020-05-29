#pragma once
#include "Color.h"

namespace Zorlock {


	class Environment
	{
	public:
		Environment();
		~Environment();
		ColorRGBA GetAmbient();
		void SetAmbient(ColorRGBA col);

	protected:
		ColorRGBA m_ambient;
	};

}