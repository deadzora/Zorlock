#pragma once

#include "Zorlock/Core/Core.h"
#include "Zorlock/Core/Timestep.h"
#include "Zorlock/Events/Event.h"

namespace Zorlock {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(ZLTIME ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		
		std::string m_DebugName;
	};

}

#define ZLLAYER Zorlock::Layer