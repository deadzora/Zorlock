#pragma once
#include "EditorGameObject.h"

namespace Zorlock {

	class EditorCamera : public EditorGameObject
	{
	public:
		virtual void Inspector(GameObject* go) override;
	};

}