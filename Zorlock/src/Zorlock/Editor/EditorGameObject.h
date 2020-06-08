#pragma once
#include "EditorObjectBase.h"

namespace Zorlock {

	class GameObject;

	class EditorGameObject : public EditorObjectBase
	{
	public:
		virtual void Inspector(void* go) override;

		virtual void Inspector(GameObject* go);
	};


}