#include "ZLpch.h"
#include "Material.h"


namespace Zorlock
{
	Material::Material()
	{
	}

	Material::Material(const Ref<Shader>& shader)
	{
		m_Shader = shader;
	}
	Material::Material(const std::string shadername)
	{
		m_Shader = ShaderLibrary::Instance()->Get(shadername);
	}
	void Material::Apply()
	{
		//apply cbuffers/uniforms - vbuffer & pbuffers
		m_Shader->Apply();
	}
	bool Material::Process()
	{


		return false;
	}
}
