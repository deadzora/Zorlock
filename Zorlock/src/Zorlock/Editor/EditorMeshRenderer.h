#pragma once
#include "EditorComponent.h"

namespace Zorlock {

	class EditorMeshRenderer : public EditorComponent
	{
	public:
		virtual void Inspector(Component* co) override;
	};


}