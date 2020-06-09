#pragma once
#include "EditorGameObject.h"

namespace Zorlock {

	class EditorEnvironment : public EditorGameObject
	{
	public:
		virtual void Inspector(GameObject* go) override;
	};

}