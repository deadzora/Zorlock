#include "ZLpch.h"
#include "EditorGameObject.h"
#include "EditorMeshRenderer.h"
#include "imgui.h"
#include "Zorlock/ImGui/IconsForkAwesome.h"
#include "Zorlock/Game/GameObject.h"
#include "Zorlock/Components/MeshRenderer.h"
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
		ImGui::Text(ICON_FK_DOT_CIRCLE_O" Components");
		ImGui::Separator();
		std::vector<Ref<Component>>& components = go->GetComponents();
		for (size_t i = 0; i < components.size(); i++)
		{
			if (components[i]->GetType().compare("MeshRenderer")==0)
			{
				EditorObjectBase::Draw<EditorMeshRenderer, Component>(components[i].get());
			}
			else {
				ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
				std::string componenttype = ICON_FK_DOT_CIRCLE_O + components[i]->GetType();
				ImGui::Text(componenttype.c_str());
				ImGui::Separator();
			}
		}
	}

}