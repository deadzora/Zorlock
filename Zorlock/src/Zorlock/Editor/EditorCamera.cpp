#include "ZLpch.h"
#include "EditorCamera.h"
#include "imgui.h"
#include "Zorlock/ImGui/IconsForkAwesome.h"
#include "Zorlock/Renderer/Camera.h"

namespace Zorlock
{
	void Zorlock::EditorCamera::Inspector(GameObject* go)
	{
		EditorGameObject::Inspector(go);
		ImGui::Separator();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		ImGui::Text(ICON_FK_DOT_CIRCLE_O" Test Camera shit");
		ImGui::Separator();
	}
}
