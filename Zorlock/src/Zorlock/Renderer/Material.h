#pragma once
#include "Shader.h"
#include "Light.h"
#include "Color.h"
#include "Texture.h"

#define ZLMATERIAL Zorlock::Material
#define ZLMATERIALLIBRARY Zorlock::MaterialLibrary
#define ZMAXLIGHTS 16

namespace Zorlock {

	struct LightBase;

	struct MatSurfaceProperties
	{
		MatSurfaceProperties() : specular(0.5), shininess(16)
		{}
		float specular;
		float shininess;
	};

	class Material {
	public:
		Material();
		Material(const Ref<Shader>& shader);
		Material(const std::string name);
		Material(const std::string name, const std::string shaderfile);
		void Apply();

		virtual ~Material()
		{};
		Ref<Shader> GetShader();
		void LoadTexture(const std::string filename);
		void LoadTexture(uint32_t width, uint32_t height, uint32_t color);
		void SetViewMatrix(MATRIX4 view);
		void SetLight(LightBase s, uint32_t index = 0);
		void ApplyViewMatrix();
		void ApplyTransform(MATRIX4 transform);
		void ApplyMainTexture();
		void ApplyLights();
		void ApplyBuffer(std::string name, void* buffer, uint32_t size, uint32_t count = 1);
		void ApplySurface();
		void SetShininess(float s);
		float GetShininess();
		void SetSpecular(float s);
		float GetSpecular();
		std::string name;
		COLOR4 materialColor;
		Ref<Texture2D> sharedTexture;
	protected:
		MATRIX4 m_viewmatrix;
		bool Process();
		Ref<Shader> m_Shader;
		std::vector <Ref<Texture2D>> m_textures;
		std::vector <LightBase> m_lights;
		MatSurfaceProperties m_surfaceProps;
	};

	class MaterialLibrary
	{
	public:
		MaterialLibrary();
		Ref<Material> GetMaterial(std::string name);
		Ref<Material> CreateMaterial(std::string name);
		Ref<Material> CreateMaterial(Ref<Shader> shader);
		Ref<Material> CreateMaterial(std::string name, std::string shaderfile);
		void AddMaterial(Ref<Material> material);
		void RemoveMaterial(std::string name);
		void RemoveMaterial(Ref<Material> material);
		static Ref<MaterialLibrary> GetInstance();
	private:
		std::vector<Ref<Material>> m_materials;
	};

	ZL_ENABLE_TYPENAME(Material)

}

#define ZLMATLIBRARY Zorlock::MaterialLibrary::GetInstance()

