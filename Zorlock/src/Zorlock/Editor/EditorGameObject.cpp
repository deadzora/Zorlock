#include "ZLpch.h"
#include "EditorGameObject.h"
#include "imgui.h"
#include "Zorlock/ImGui/IconsForkAwesome.h"
#include "Zorlock/Game/GameObject.h"

namespace Zorlock
{
	void EditorGameObject::Inspector(void* go)
	{
		GameObject* gobj = static_cast<GameObject*>(go);
		Inspector(gobj);
	}

	void EditorGameObject::Inspector(GameObject* go)
	{
		ImGui::Separator();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		ImGui::Text(ICON_FK_DOT_CIRCLE_O" Test Game Object yo");
		ImGui::Separator();
	}

}