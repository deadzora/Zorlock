#pragma once

#include "Zorlock/Layer.h"

#include "Zorlock/Events/ApplicationEvent.h"
#include "Zorlock/Events/KeyEvent.h"
#include "Zorlock/Events/MouseEvent.h"

namespace Zorlock
{
	class ZORLOCK_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
		float m_Time = 0.0f;
	};
}