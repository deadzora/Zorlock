#pragma once
#include "Zorlock/Game/Component.h"
#include "Zorlock/Renderer/Material.h"

namespace Zorlock {


	class ObjectRenderer : public Component
	{
	public:
		ObjectRenderer();
		ObjectRenderer(std::string name);
		~ObjectRenderer();
		virtual void Awake() override;
		virtual void Start() override;
		virtual void Update(Timestep ts) override;
		virtual void Render() override;
		virtual void Destroy() override;
		virtual void AddMaterial(Ref<Material> material);
		virtual void AddMaterial(Ref<Material> material, size_t index);
		virtual void RemoveMaterial(size_t index);
		virtual void RemoveMaterial(Ref<Material> material);
		Ref<Material> GetMaterial(size_t index);
		Ref<Material> GetMaterial(std::string matname);
		std::vector<Ref<Material>>& GetMaterials();



	protected:
		std::vector<Ref<Material>> m_materials;
	};


}