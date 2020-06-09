#pragma once
#include "ObjectRenderer.h"




namespace Zorlock {
	
	class ZModel;
	class Mesh;

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
		bool CreateQuad();
		bool CreateCube();
		bool CreateSphere(uint32_t segments);
		bool CreateCylinder(uint32_t segments);
		bool CreateCone(uint32_t segments);
		bool AddModel(const std::string& name, const std::string& filename, const float scale = 1.0f);
		void AppendAnimation(const std::string& filename, uint32_t modelindex = 0);
		Ref<ZModel> GetModel(uint32_t index);
		Ref<Mesh> GetMesh(uint32_t index, uint32_t indexb);
		void RemoveModel(std::string name);
		void RemoveModel(Ref<ZModel> model);

	protected:
		
		std::vector<Ref<ZModel>> m_models;
	};
	
	ZL_ENABLE_TYPENAME(MeshRenderer)
}

#define ZLMESHRENDERER Zorlock::MeshRenderer

