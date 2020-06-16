#pragma once
#include "Zorlock/Events/ApplicationEvent.h"
#include "Zorlock/Events/MouseEvent.h"
#include "Zorlock/Core/Timestep.h"

namespace Zorlock {

	class EditorCameraControl
	{

		static void OnUpdate(Timestep ts);
		static void OnEvent(Event& e);


	};




}