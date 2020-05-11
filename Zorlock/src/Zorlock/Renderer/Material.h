#pragma once
#include "Shader.h"

namespace Zorlock {

	class Material {
	public:
		virtual ~Material() = default;
	protected:
		std::shared_ptr<Shader> m_Shader;
	};


}