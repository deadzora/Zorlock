#pragma once
#include "Zorlock/Game/Behavior.h"
#include "Zorlock/Renderer/Material.h"

namespace Zorlock {


	class ObjectRenderer : public Behavior
	{
	public:
		ObjectRenderer();
		virtual ~ObjectRenderer() override;
		virtual void Awake() const override;
		virtual void Start() const override;
		virtual void Update() const override;
		virtual void Destroy() const override;
	protected:
		std::vector<Material> m_materials;
	};


}