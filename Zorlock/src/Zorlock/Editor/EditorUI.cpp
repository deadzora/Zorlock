#include "ZLpch.h"
#include "EditorUI.h"
#include "imgui.h"
#include "Zorlock/ImGui/ImGuiSkins.h"
#include "Zorlock/Core/Application.h"
#include "Zorlock/Game/SceneManager.h"
#include "Zorlock/Renderer/Environment.h"
#include "ProjectManager.h"
#include "Projects.h"
#include "Assets.h"
#include "Zorlock/ImGui/ImGuiSkins.h"
#include "Zorlock/ImGui/IconsForkAwesome.h"
#include <map>
#include "EditorObjectBase.h"
#include "EditorGameObject.h"
#include "EditorCamera.h"
#include "EditorLight.h"
#include "EditorEnvironment.h"
#include "EditorFunctions.h"
namespace Zorlock
{
	
	

	static bool changetheme = false;
	static size_t current_theme = 0;
	static EditorUI* editorUI = nullptr;
	static GameObject* selectedObject = nullptr;


	EditorUI::EditorUI()
	{
		
	}

	EditorUI::~EditorUI()
	{
	}

	void EditorUI::EditorUIDraw()
	{
		
		//ImGuiSkin::PushFont();
		if (!ProjectManager::Get()->IsProjectLoaded())
		{
			ProjectSelection();
		}
		else {
			MainEditor();
		}
		//ImGui::PopFont();
	}


	void EditorUI::MainEditor()
	{


		AssetExplorer();
		Inspector();
		MainMenu();
		ToolBarTop();
		ToolBarBottom();

		if (changetheme)
		{
			ImGuiSkin::SetSkin(current_theme);
			changetheme = false;
		}
	}


	void EditorUI::ProjectSelection()
	{
		
		Project* cproj = ProjectManager::Get()->GetCurrentProject();
		static char InputBuf[256];
		strcpy(InputBuf, cproj->Name().c_str());
		ImGui::SetNextWindowPosCenter(ImGuiCond_::ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(Application::Get().GetWindow().GetWidth() / 2, Application::Get().GetWindow().GetHeight() / 2), ImGuiCond_::ImGuiCond_FirstUseEver);
		ImGui::Begin("New Project", 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove | ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar);
		
		ImGui::BeginChild("Project List", ImVec2(ImGui::GetWindowWidth() / 4, 0), true);
		ProjectsList();	
		cproj = ProjectManager::Get()->GetCurrentProject();
		strcpy(InputBuf, cproj->Name().c_str());
		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginGroup();
		ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing() - 30)); // Leave room for 1 line below us
		ImGui::Text("Create New Project");
		ImGui::Separator();
		if (ProjectManager::Get()->IsNewProject())
		{
			if (ImGui::InputText(ICON_FK_PENCIL" :Project Name", InputBuf, IM_ARRAYSIZE(InputBuf)))
			{
				char* input_end = InputBuf + strlen(InputBuf);
				while (input_end > InputBuf&& input_end[-1] == ' ') input_end--; *input_end = 0;
				cproj->Name(InputBuf);
			}
		}
		else {

			ImGui::TextWrapped(ICON_FK_FOLDER_O" %s ", InputBuf);
		}
		ImGui::Separator();
		std::string projdir = "\n" + cproj->Directory() + "\\" + cproj->Name();
		ImGui::TextWrapped(ICON_FK_FOLDER_O" %s ", projdir.c_str());
		ImGui::EndChild();
		ImGui::BeginChild("buttons");
		if (ImGui::Button(ICON_FK_TIMES" Exit", ImVec2((ImGui::GetContentRegionAvail().x * 0.5f) - 10, 30))) {}
		ImGui::SameLine();
		if (ProjectManager::Get()->IsNewProject())
		{
			if (ImGui::Button(ICON_FK_CHECK" Create", ImVec2((ImGui::GetContentRegionAvail().x) - 10, 30))) {
			
				ProjectManager::Get()->CreateProject();
			}
		}
		else {
			if (ImGui::Button(ICON_FK_CHECK" Load", ImVec2((ImGui::GetContentRegionAvail().x) - 10, 30))) {
				ProjectManager::Get()->LoadProject();
			}
		}
		ImGui::EndChild();
		ImGui::EndGroup();
		ImGui::End();
	}

	void EditorUI::ProjectsList()
	{

		if (ImGui::Button(ICON_FK_STAR" < New Project >", ImVec2((ImGui::GetContentRegionAvail().x), 30)))
		{
			ProjectManager::Get()->SetNewProject();
		}
		ImGui::Separator();

		Projects* projects = ProjectManager::Get()->GetProjects();
		std::vector<Project>& _p = ProjectManager::Get()->GetProjects()->ProjectsList();

		for (size_t i = 0; i < _p.size(); i++)
		{
			std::string pname = ICON_FK_FOLDER_O" " + _p[i].Name() + " ";
			if (ImGui::Button(pname.c_str(), ImVec2((ImGui::GetContentRegionAvail().x), 30)))
			{
				ProjectManager::Get()->SetProject(i);
			}
			ImGui::Separator();
		}



	}



	void EditorUI::MainMenu()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem(ICON_FK_FILE_O" New Scene", "CTRL+N")) {}
				if (ImGui::MenuItem(ICON_FK_FILE_O" Open Scene", "CTRL+O")) {}
				if (ImGui::MenuItem(ICON_FK_FLOPPY_O" Save Scene", "CTRL+S")) {}
				ImGui::Separator();
				if (ImGui::MenuItem(ICON_FK_FLOPPY_O" Save Project", "CTRL+ALT+S")) {}
				ImGui::Separator();
				if (ImGui::MenuItem(ICON_FK_ARROW_CIRCLE_O_DOWN" Import Asset", "CTRL+I")) {}
				if (ImGui::MenuItem(ICON_FK_ARROW_CIRCLE_O_UP" Export Asset", "CTRL+E")) {}
				ImGui::Separator();
				if (ImGui::MenuItem(ICON_FK_POWER_OFF" Quit", "CTRL+Q")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem(ICON_FK_REPLY" Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem(ICON_FK_SHARE" Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem(ICON_FK_SCISSORS" Cut", "CTRL+X")) {}
				if (ImGui::MenuItem(ICON_FK_FILES_O" Copy", "CTRL+C")) {}
				if (ImGui::MenuItem(ICON_FK_PAPERCLIP" Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Object"))
			{
				if (ImGui::MenuItem(ICON_FK_CIRCLE_THIN" Create Empty", "CTRL+SHIFT+N")) {}
				ImGui::Separator();
				if (ImGui::BeginMenu(ICON_FK_CUBE" 3D")) {
					if (ImGui::MenuItem(ICON_FK_CUBE" Cube")) 
					{
						EditorFunctions::CreateCube("Cube");
					}
					if (ImGui::MenuItem(ICON_FK_CIRCLE_O" Sphere")) {}
					if (ImGui::MenuItem(ICON_FK_SQUARE_O" Cylinder")) {}
					if (ImGui::MenuItem(ICON_FK_GLASS" Cone")) {}
					if (ImGui::MenuItem(ICON_FK_TH_LARGE" Quad")) {}
					ImGui::Separator();
					if (ImGui::MenuItem(ICON_FK_AREA_CHART" Terrain")) {}
					ImGui::EndMenu();
				}
				ImGui::Separator();
				if (ImGui::MenuItem(ICON_FK_LIGHTBULB_O" Light", "CTRL+V"))
				{
					EditorFunctions::CreateLight("Light");
				}
				ImGui::EndMenu();

			}

			ImGui::EndMainMenuBar();

		}
	}

	void EditorUI::AssetExplorer()
	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowViewport()->Pos.x, ImGui::GetWindowViewport()->Pos.y+ImGui::GetTextLineHeightWithSpacing()), ImGuiCond_::ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(ImGui::GetWindowViewport()->Size.x / 6, ImGui::GetWindowViewport()->Size.y-ImGui::GetTextLineHeightWithSpacing()), ImGuiCond_::ImGuiCond_FirstUseEver);
		
		ImGui::Begin("Assets", 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove | ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar);
		
		ImGui::BeginChild("Top", ImVec2(ImGui::GetContentRegionMax().x, ImGui::GetContentRegionMax().y/2),false,ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar);
		if (ImGui::BeginTabBar("Tabs"))
		{
			if (ImGui::BeginTabItem(ICON_FK_DESKTOP" Explorer"))
			{

				//ImGuiSkin::PushIconFont();
				if (ImGui::Button(ICON_FK_FOLDER" New Folder "))
				{

				}
				ImGui::SameLine();
				if (ImGui::Button(ICON_FK_FILE_O" New Asset "))
				{

				}
				
				//ImGui::BeginChild("Asset Child", ImVec2(ImGui::GetContentRegionMax().x, ImGui::GetContentRegionMax().y), false, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysVerticalScrollbar);
				//ImGui::PopFont();
				//ImGuiSkin::PushFont();
				if (ImGui::TreeNode(ICON_FK_CUBE" Assets"))
				{
					if (ImGui::Button("Button"))
					{

					}
					ImGui::TreePop();
				}

				//ImGui::EndChild();

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(ICON_FK_CLOCK_O" Recent"))
			{
				ImGui::EndTabItem();
			}
			
			ImGui::EndTabBar();
		}
		
		ImGui::EndChild();

		ImGui::BeginChild("Bottom",ImVec2(ImGui::GetContentRegionMax().x, ImGui::GetContentRegionMax().y/2), false , ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar);
		
		if (ImGui::BeginTabBar("Tabs"))
		{
			if (ImGui::BeginTabItem(ICON_FK_SITEMAP" Heirarchy"))
			{
				
				//ImGui::BeginChild("Heirarchy Child", ImVec2(ImGui::GetContentRegionMax().x, ImGui::GetContentRegionMax().y), false, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysVerticalScrollbar);
				if (SceneManager::GetInstance()->GetActiveScene() != nullptr)
				{
					std::string sname = SceneManager::GetInstance()->GetActiveScene()->name;
					sname = ICON_FK_CUBES + sname;
					if (ImGui::TreeNode(sname.c_str()))
					{
						
						Environment* env = SceneManager::GetInstance()->GetActiveScene()->GetEnvironment().get();
						std::string envtext = ICON_FK_SUN_O" " + env->name;
						
						if (ImGui::TreeNode("Lights"))
						{
							std::vector<Ref<Light>>& lights = SceneManager::GetInstance()->GetActiveScene()->GetSceneLights();
							for (size_t l = 0; l < lights.size(); l++)
							{
								std::string lighttext = ICON_FK_LIGHTBULB_O" " + lights[l]->name;
								if (ImGui::Selectable(lighttext.c_str(), (selectedObject == lights[l].get())))
								{
									selectedObject = lights[l].get();

								}
							}
							ImGui::TreePop();
						}

						if (ImGui::Selectable(envtext.c_str(), (selectedObject == env)))
						{
							selectedObject = env;
							
						}
						std::vector<Ref<GameObject>>& gameobjs = SceneManager::GetInstance()->GetActiveScene()->GetChildren();
						for (size_t i = 0; i < gameobjs.size(); i++)
						{
							std::string buttontext = ImGuiSkin::GetTypeIcon(gameobjs[i]->GetType()) + " " + gameobjs[i]->name;
							if (ImGui::Selectable(buttontext.c_str(),(selectedObject== gameobjs[i].get())))
							{
								selectedObject = gameobjs[i].get();
					
							}
						}
						ImGui::TreePop();
					}
					ImGui::EndTabItem();
				}
				//ImGui::EndChild();
			}
			ImGui::EndTabBar();
		}
		
		ImGui::EndChild();
		ImGui::End();
	}

	void EditorUI::Inspector()
	{
		static char NameInputBuf[256];
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowViewport()->Pos.x+ImGui::GetWindowViewport()->Size.x-(ImGui::GetWindowViewport()->Size.x / 6), ImGui::GetWindowViewport()->Pos.y + ImGui::GetTextLineHeightWithSpacing()), ImGuiCond_::ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(ImGui::GetWindowViewport()->Size.x / 6, ImGui::GetWindowViewport()->Size.y - ImGui::GetTextLineHeightWithSpacing()), ImGuiCond_::ImGuiCond_FirstUseEver);

		ImGui::Begin("Inspector", 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove | ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar);
		if (ImGui::BeginTabBar("Tabs"))
		{
			if (ImGui::BeginTabItem(ICON_FK_SEARCH" Inspector"))
			{
				if (selectedObject != nullptr)
				{
					std::string buttontext = ImGuiSkin::GetTypeIcon(selectedObject->GetType()) + " " + selectedObject->name;
					strcpy(NameInputBuf, selectedObject->name.c_str());
					if (ImGui::InputText(ICON_FK_PENCIL" :Name", NameInputBuf, IM_ARRAYSIZE(NameInputBuf)))
					{
						char* input_end = NameInputBuf + strlen(NameInputBuf);
						while (input_end > NameInputBuf&& input_end[-1] == ' ') input_end--; *input_end = 0;
						selectedObject->name = NameInputBuf;
					}
					TransformBlock();
					GameObjectBlock();
				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
	}

	void EditorUI::ToolBarTop()
	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowViewport()->Pos.x+(ImGui::GetWindowViewport()->Size.x / 6)-30, ImGui::GetWindowViewport()->Pos.y + ImGui::GetTextLineHeightWithSpacing()), ImGuiCond_::ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(ImGui::GetWindowViewport()->Size.x-((ImGui::GetWindowViewport()->Size.x / 6)*2)+60, ImGui::GetTextLineHeightWithSpacing()), ImGuiCond_::ImGuiCond_FirstUseEver);
		ImGui::Begin("ToolBar Top", 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove | ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_::ImGuiWindowFlags_NoFocusOnAppearing);
		ImGui::SetCursorPosX(60);
		ImGui::SetCursorPosY(5);
		if (ImGui::Button(ICON_FK_MOUSE_POINTER))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button(ICON_FK_ARROWS))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button(ICON_FK_REPEAT))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button(ICON_FK_ARROWS_ALT))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button(ICON_FK_VIDEO_CAMERA" Editor"))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button(ICON_FK_VIDEO_CAMERA" Scene"))
		{
		}
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x-((ImGui::CalcTextSize(ICON_FK_TINT" Skin").x)+(ImGui::CalcTextSize(skins[0]).x*3)));
		ImGui::SetNextItemWidth(ImGui::CalcTextSize(skins[0]).x*2);
		if (ImGui::BeginCombo(ICON_FK_TINT" Skin", skin_current,ImGuiComboFlags_::ImGuiComboFlags_PopupAlignLeft))
		{
			for (size_t n = 0; n < IM_ARRAYSIZE(skins); n++)
			{
				bool is_selected = (skin_current == skins[n]);
				if (ImGui::Selectable(skins[n], is_selected,0, ImGui::CalcTextSize(skins[0])))
				{
					skin_current = skins[n];
					current_theme = n;
					changetheme = true;
					//ImGuiSkin::SetSkin(n);
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::End();
	}

	void EditorUI::ToolBarBottom()
	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowViewport()->Pos.x + (ImGui::GetWindowViewport()->Size.x / 6) - 30, ImGui::GetWindowViewport()->Pos.y + (ImGui::GetWindowViewport()->Size.y - (ImGui::GetTextLineHeightWithSpacing()*2))),ImGuiCond_::ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(ImGui::GetWindowViewport()->Size.x - ((ImGui::GetWindowViewport()->Size.x / 6) * 2) + 60, ImGui::GetTextLineHeightWithSpacing()*2), ImGuiCond_::ImGuiCond_FirstUseEver);
		ImGui::Begin("ToolBar Bottom", 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove | ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_::ImGuiWindowFlags_NoFocusOnAppearing);
		ImGui::SetCursorPosX(60);
		ImGui::SetCursorPosY(5);

		ImGui::End();
	}

	void EditorUI::GameObjectBlock()
	{
		if (selectedObject != nullptr)
		{
			if (selectedObject->GetType().compare("GameObject")==0)
			{
				EditorObjectBase::Draw<EditorGameObject, GameObject>(selectedObject);
			}
			if (selectedObject->GetType().compare("Camera")==0)
			{
				EditorObjectBase::Draw<EditorCamera, GameObject>(selectedObject);
			}
			if (selectedObject->GetType().compare("Environment") == 0)
			{
				EditorObjectBase::Draw<EditorEnvironment, GameObject>(selectedObject);
			}
			if (selectedObject->GetType().compare("Light") == 0)
			{
				EditorObjectBase::Draw<EditorLight, GameObject>(selectedObject);
			}
		}
	}

	void EditorUI::TransformBlock()
	{
		if (selectedObject != nullptr)
		{
			Vector3 pos = selectedObject->transform->position;
			Quaternion rot = selectedObject->transform->rotation;
			Vector3 scale = selectedObject->transform->scale;
			ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
			ImGui::Text(ICON_FK_DOT_CIRCLE_O" Transform");	
			ImGui::Separator();
			ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
			ImGui::Text(ICON_FK_ARROWS" Position");
			ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
			if (ImGui::InputFloat3("Position", &pos.x))
			{
				selectedObject->transform->position = pos;
			}
			ImGui::Separator();
			ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
			ImGui::Text(ICON_FK_REPEAT" Rotation");
			ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
			if (ImGui::InputFloat4("Rotation", &rot.x))
			{
				selectedObject->transform->rotation = rot;
			}
			ImGui::Separator();
			ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
			ImGui::Text(ICON_FK_ARROWS_ALT" Scale");
			ImGui::SetNextItemWidth(ImGui::GetContentRegionMax().x);
			if (ImGui::InputFloat3("Scale", &scale.x))
			{
				selectedObject->transform->scale = scale;
			}
			ImGui::Separator();
		}
	}



		EditorUI* EditorUI::Get()
	{
		if (editorUI == nullptr)
			editorUI = new EditorUI();
		return editorUI;
	}


}