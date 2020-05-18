#pragma once
#include "Shader.h"

namespace Zorlock {

	class Material {
	public:
		Material();
		Material(const Ref<Shader>& shader);
		Material(const std::string shadername);
		void Apply();

		virtual ~Material()
		{};
	protected:
		bool Process();
		Ref<Shader> m_Shader;
	};


}