#include "ZLpch.h"
#include "EditorCamera.h"
#include "imgui.h"
#include "Zorlock/ImGui/IconsForkAwesome.h"
#include "Zorlock/Renderer/Camera.h"

namespace Zorlock
{
	void Zorlock::EditorCamera::Inspector(GameObject* go)
	{	
		Camera* cam = static_cast<Camera*>(go);
		ImGui::Separator();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		ImGui::Text(ICON_FK_VIDEO_CAMERA" Camera Settings");
		ImGui::Separator();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		ImGui::Text(ICON_FK_EYE" Field of View");
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		float efov = cam->FOV();
		if (ImGui::InputFloat("FOV", &efov))
		{
			cam->FOV(efov);
		}
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		ImGui::Text(ICON_FK_EXPAND" Aspect Ratio");
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		float aratio = cam->AspectRatio();
		if (ImGui::InputFloat("AspectRatio", &aratio))
		{
			cam->AspectRatio(aratio);
		}
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		ImGui::Text(ICON_FK_ARROW_DOWN" Near");
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		float enearz = cam->NearZ();
		if (ImGui::InputFloat("NearZ", &enearz))
		{
			cam->NearZ(enearz);
		}
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		ImGui::Text(ICON_FK_ARROW_UP" Far");
		ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
		float efarz = cam->FarZ();
		if (ImGui::InputFloat("FarZ", &efarz))
		{
			cam->FarZ(efarz);
		}
		ImGui::Separator();
		EditorGameObject::Inspector(go);
	}
}
