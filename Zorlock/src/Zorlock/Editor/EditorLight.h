#pragma once
#include "EditorGameObject.h"

namespace Zorlock {

	class EditorLight : public EditorGameObject
	{
	public:
		virtual void Inspector(GameObject* go) override;
	};

}