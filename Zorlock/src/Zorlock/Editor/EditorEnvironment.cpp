#include "ZLpch.h"
#include "EditorEnvironment.h"
#include "imgui.h"
#include "Zorlock/ImGui/IconsForkAwesome.h"
#include "Zorlock/Renderer/Environment.h"

namespace Zorlock
{
	void EditorEnvironment::Inspector(GameObject* go)
	{

		Environment* env = static_cast<Environment*>(go);
		ImGui::Separator();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		ImGui::Text(ICON_FK_SUN_O" Ambient Light");
		ColorRGBA col = env->GetAmbient();
		if (ImGui::ColorEdit4("AMBColor", &col.x,ImGuiColorEditFlags_::ImGuiColorEditFlags_Float))
		{
			
			env->SetAmbient(col);
		}
		ImGui::Separator();
		EditorGameObject::Inspector(go);
	}


}