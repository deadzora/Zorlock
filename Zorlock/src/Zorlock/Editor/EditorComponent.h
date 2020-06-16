#pragma once
#include "EditorObjectBase.h"

namespace Zorlock {

	class Component;

	class EditorComponent : public EditorObjectBase
	{
	public:
		virtual void Inspector(void* co) override;
		virtual void Inspector(Component* co) = 0;
	};
}