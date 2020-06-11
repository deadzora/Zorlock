#include "ZLpch.h"
#include "EditorLight.h"
#include "imgui.h"
#include "Zorlock/ImGui/IconsForkAwesome.h"
#include "Zorlock/Renderer/Light.h"

namespace Zorlock
{

	void EditorLight::Inspector(GameObject* go)
	{
		Light* light = static_cast<Light*>(go);
		ImGui::Separator();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		ImGui::Text(ICON_FK_SUN_O" Light Color");
		ColorRGBA col = light->GetColor();
		if (ImGui::ColorEdit4("LColor", &col.x, ImGuiColorEditFlags_::ImGuiColorEditFlags_Float))
		{

			light->SetColor(col);
		}
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		ImGui::Separator();
		float rd = light->GetRadius();
		if (ImGui::InputFloat(ICON_FK_CROSSHAIRS" Radius", &rd))
		{
			light->SetRadius(rd);
		}
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		ImGui::Separator();
		float str = light->GetStrength();
		if (ImGui::InputFloat(ICON_FK_FREE_CODE_CAMP" Strength", &str))
		{
			light->SetStrength(str);
		}
		ImGui::Separator();
		EditorGameObject::Inspector(go);
	}


}