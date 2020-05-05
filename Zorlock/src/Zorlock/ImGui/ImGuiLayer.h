#pragma once

#include "Zorlock/Core/Layer.h"

#include "Zorlock/Events/ApplicationEvent.h"
#include "Zorlock/Events/KeyEvent.h"
#include "Zorlock/Events/MouseEvent.h"

namespace Zorlock {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}