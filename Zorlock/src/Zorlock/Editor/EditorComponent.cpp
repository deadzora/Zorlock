#include "ZLpch.h"
#include "EditorComponent.h"
#include "imgui.h"
#include "Zorlock/ImGui/IconsForkAwesome.h"
#include "Zorlock/Game/Component.h"

void Zorlock::EditorComponent::Inspector(void* co)
{
	Component* component = static_cast<Component*>(co);
	Inspector(component);
}


