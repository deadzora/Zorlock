#include "ZLpch.h"
#include "EditorMeshRenderer.h"
#include "imgui.h"
#include "Zorlock/ImGui/IconsForkAwesome.h"
#include "Zorlock/Components/MeshRenderer.h"
#include "Zorlock/Renderer/Material.h"


void Zorlock::EditorMeshRenderer::Inspector(Component* co)
{
	MeshRenderer* mr = static_cast<MeshRenderer*>(co);
	ImGui::Separator();
	ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
	ImGui::Text(ICON_FK_CONNECTDEVELOP" Mesh Renderer");
	ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
	ImGui::Separator();
	std::vector<Ref<Material>>& mats = mr->GetMaterials();
	for (size_t i = 0; i <mats.size(); i++)
	{
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		
		std::string mname = ICON_FK_TINT" ["+ std::to_string(i)+"] "+mats[i]->name;
		ImGui::Text(mname.c_str());

	}
	ImGui::Separator();
}
