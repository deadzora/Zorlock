#pragma once
#include "ObjectRenderer.h"




namespace Zorlock {
	
	class Model;

	class MeshRenderer : public ObjectRenderer
	{
	public:
		MeshRenderer();
		MeshRenderer(std::string name);
		~MeshRenderer();
		virtual void Awake() override;
		virtual void Start() override;
		virtual void Update(Timestep ts) override;
		virtual void Render() override;
		virtual void Destroy() override;
		bool AddModel(const std::string& name, const std::string& filename);
		Ref<Model> GetModel(uint32_t index);
		void RemoveModel(std::string name);
		void RemoveModel(Ref<Model> model);

	protected:
		
		std::vector<Ref<Model>> m_models;
	};
	
	
}

#define ZLMESHRENDERER Zorlock::MeshRenderer

