#include "ZLpch.h"
#include "Material.h"


namespace Zorlock
{
	MaterialLibrary materialLibrary;
	Ref<MaterialLibrary> m_materialLibrary;

	Material::Material() : name("material") , m_viewmatrix(MATRIX4::IDENTITY())
	{
		m_lights.resize(ZMAXLIGHTS, LightBase());
	}

	Material::Material(const Ref<Shader>& shader) : name(shader->GetName()), m_viewmatrix(MATRIX4::IDENTITY())
	{
		m_Shader = shader;
		m_lights.resize(ZMAXLIGHTS, LightBase());
	}
	Material::Material(const std::string name) : name(name), m_viewmatrix(MATRIX4::IDENTITY())
	{
		m_lights.resize(ZMAXLIGHTS, LightBase());
		//m_Shader = ShaderLibrary::GetInstance()->Get(shadername);
	}
	Material::Material(const std::string name, const std::string shaderfile): name(name), m_viewmatrix(MATRIX4::IDENTITY())
	{
		m_Shader = Shader::Create(name, shaderfile);
		m_lights.resize(ZMAXLIGHTS, LightBase());
	}
	void Material::Apply()
	{
		//apply cbuffers/uniforms - vbuffer & pbuffers
		m_Shader->Apply();
	}
	Ref<Shader> Material::GetShader()
	{
		return m_Shader;
	}
	void Material::LoadTexture(const std::string filename)
	{
		Ref<Texture2D> tex = Texture2D::Create(filename);
		if (tex != nullptr)
		{
			if (m_textures.size() == 0)
			{
				sharedTexture = tex;
			}
			m_textures.push_back(tex);
		}

	}
	void Material::LoadTexture(uint32_t width, uint32_t height, uint32_t color)
	{
		Ref<Texture2D> tex = Texture2D::Create(width,height,color);
		if (tex != nullptr)
		{
			if (m_textures.size() == 0)
			{
				sharedTexture = tex;
			}
			m_textures.push_back(tex);
		}
	}
	void Material::SetViewMatrix(MATRIX4 view)
	{
		m_viewmatrix = view;
	}
	void Material::SetLight(LightBase s, uint32_t index)
	{
		m_lights[index] = s;
	}
	void Material::ApplyViewMatrix()
	{
		if (m_Shader != nullptr)
		{
			
			m_Shader->Bind();
			m_Shader->SetMat4("u_ViewProjection", m_viewmatrix);
		}
	}
	void Material::ApplyTransform(MATRIX4 transform)
	{
		if (m_Shader != nullptr)
		{
			
			m_Shader->Bind();
			m_Shader->SetMat4("u_Transform", transform);
		}
	}
	void Material::ApplyMainTexture()
	{
		if (sharedTexture != nullptr)
		{
			if (m_Shader != nullptr)
			{
				uint32_t i = 0;
				//m_Shader->SetInt("u_Texture", 0);
				//m_Shader->Bind();
				
				sharedTexture->Bind();
				
			}
		}
	}
	bool Material::Process()
	{


		return false;
	}
	Ref<MaterialLibrary> MaterialLibrary::GetInstance()
	{
		if (m_materialLibrary == nullptr)
		{
			m_materialLibrary = CreateRef<MaterialLibrary>(materialLibrary);
		}

		return m_materialLibrary;
	}

	MaterialLibrary::MaterialLibrary()
	{
	}

	Ref<Material> MaterialLibrary::GetMaterial(std::string name)
	{
		for (size_t i = 0; i < m_materials.size(); i++)
		{
			if (m_materials[i]->name.compare(name) == 0)
			{
				return m_materials[i];
			}
		}
		return nullptr;
	}
	Ref<Material> MaterialLibrary::CreateMaterial(std::string name)
	{
		Ref<Material> mat = CreateRef<Material>(name);

		return mat;
	}
	Ref<Material> MaterialLibrary::CreateMaterial(Ref<Shader> shader)
	{
		Ref<Material> mat = CreateRef<Material>(shader);

		return mat;
	}
	Ref<Material> MaterialLibrary::CreateMaterial(std::string name, std::string shaderfile)
	{
		Ref<Material> mat = CreateRef<Material>(name, shaderfile);

		return mat;
	}
	void MaterialLibrary::AddMaterial(Ref<Material> material)
	{
		m_materials.push_back(material);
	}
	void MaterialLibrary::RemoveMaterial(std::string name)
	{
		for (size_t i = 0; i < m_materials.size(); i++)
		{
			if (m_materials[i]->name.compare(name) == 0)
			{
				m_materials.erase(m_materials.begin() + (i));
				m_materials.shrink_to_fit();
				return;
			}
		}
	}
	void MaterialLibrary::RemoveMaterial(Ref<Material> material)
	{
		for (size_t i = 0; i < m_materials.size(); i++)
		{
			if (m_materials[i]==material)
			{
				m_materials.erase(m_materials.begin() + (i));
				m_materials.shrink_to_fit();
				return;
			}
		}
	}
}
