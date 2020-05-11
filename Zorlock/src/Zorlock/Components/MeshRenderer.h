#pragma once
#include "ObjectRenderer.h"
#include "Zorlock/Renderer/Mesh.h"

namespace Zorlock {
	
	
	class MeshRenderer : public ObjectRenderer
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer() override;
		virtual void Awake() const override;
		virtual void Start() const override;
		virtual void Update() const override;
		virtual void Destroy() const override;
	protected:
		std::vector<Mesh> m_meshes;
	};
	
	
}