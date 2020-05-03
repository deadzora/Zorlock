#include "EditorWindow.h"
#include "ErrorLogger.h"
//#include <plog/Log.h>

EditorWindow::EditorWindow()
{
}


EditorWindow::~EditorWindow()
{
}

void EditorWindow::OnUpdate()
{
	this->UpdateCamera();
	GraphicsEngine::get()->Cls();


	GraphicsEngine::get()->UpdateWorld();
	GraphicsEngine::get()->RenderWorld();

	//draw UI here
	this->DrawGUI();

	GraphicsEngine::get()->Flip();

}

void EditorWindow::OnCreate()
{

	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Call CoInitialize");
	}
	//Start Logger
	//plog::init(plog::debug, "EditorLog.txt");
	//PLOGD << "Init System!";

	RECT rc = this->getClientWindowRect();
	float AspectRatio = static_cast<float>((rc.right - rc.left)) / static_cast<float>((rc.bottom - rc.top));

	GraphicsEngine::get()->Init(this->m_hwnd, this->getClientWindowRect());
	this->camera = GraphicsEngine::get()->CreateCamera(AspectRatio);
}


void EditorWindow::OnDestroy()
{
	GraphicsEngine::get()->release();
	Window::OnDestroy();
}

void EditorWindow::InitGUI()
{
	//TBD
	ImGui::StyleColorsDark();
}

void EditorWindow::DrawGUI()
{

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//GUI STUFF HERE
	this->UpdateGUI();

	
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void EditorWindow::UpdateGUI()
{
	RECT rc = this->getClientWindowRect();
	float w = static_cast<float>((rc.right - rc.left));
	float h = static_cast<float>((rc.bottom - rc.top));
	
	ImGuiWindowFlags winflags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
	ImGui::Begin("Editor",0,winflags);
	ImGui::SetWindowSize(ImVec2(w, h));
	this->EditorTabs();
	//ImGui::Text("This is example text");
	ImGui::End();
	
	
}

void EditorWindow::UpdateCamera()
{
	while (!mouse.EventBufferIsEmpty())
	{
		MouseEvent me = mouse.ReadEvent();
		if (mouse.IsRightDown())
		{
			if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
			{
				this->camera->AdjustRotation((float)me.GetPosY() * 0.001f, (float)me.GetPosX() * 0.001f, 0.0f);
			}
		}
	}
	while (!keyboard.CharBufferIsEmpty())
	{
		unsigned char ch = keyboard.ReadChar();

	}
	while (!keyboard.KeyBufferIsEmpty())
	{
		unsigned char keycode = keyboard.ReadKey().GetKeyCode();

	}

	float cameraspeed = 0.002f;
	if (keyboard.KeyIsPressed(VK_SHIFT))
	{
		cameraspeed = 0.05f;
	}
	if (keyboard.KeyIsPressed('W'))
	{
		this->camera->AdjustPosition(this->camera->GetFowardVector()*cameraspeed);
	}
	if (keyboard.KeyIsPressed('S'))
	{
		this->camera->AdjustPosition(this->camera->GetBackVector()*cameraspeed);
	}
	if (keyboard.KeyIsPressed('A'))
	{
		this->camera->AdjustPosition(this->camera->GetLeftVector()*cameraspeed);
	}
	if (keyboard.KeyIsPressed('D'))
	{
		this->camera->AdjustPosition(this->camera->GetRightVector()*cameraspeed);
	}
	if (keyboard.KeyIsPressed('Q'))
	{
		this->camera->AdjustPosition(0.0f, cameraspeed, 0.0f);
	}
	if (keyboard.KeyIsPressed('E'))
	{
		this->camera->AdjustPosition(0.0f, -cameraspeed, 0.0f);
	}
	if (keyboard.KeyIsPressed('C'))
	{

	}
}

void EditorWindow::EditorTabs()
{
	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
	{
		if (ImGui::BeginTabItem("Project"))
		{
			this->ProjectTab();

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Media"))
		{
			this->MediaTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Particles"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Combat"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Projectiles"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Factions"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Animations"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Attributes"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Actors"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Items"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Days & seasons"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Zones"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Abilities"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Interface"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Other"))
		{
			ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}

void EditorWindow::ProjectTab()
{
	ImGui::Text("Welcome to Realm Weaver!");
	if (ImGui::Button("Build Full Client"))
	{

	}
	if (ImGui::Button("Build Mini Client"))
	{

	}
	if (ImGui::Button("Build Client Patch"))
	{

	}
	if (ImGui::Button("Build Server"))
	{

	}
}

void EditorWindow::MediaTab()
{
	static int item = 1;
	//ImGui::Combo("Combo", &item, "View 3D Meshes\View Textures\View Materials\View Shaders\View Sounds\View Music");
	if (ImGui::Button("Add"))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button("Remove"))
	{

	}
	ImGui::BeginGroup();

	ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
	ImGui::Separator();
	if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Meshes"))
		{
			ImGui::BeginGroup();

			if (ImGui::TreeNode("SomeFolder"))
			{
				ImGui::Text("Some Mesh A");
				ImGui::Text("Some Mesh B");
				ImGui::Text("Some Mesh C");
				ImGui::TreePop();
			}

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::Text("Preview");
			ImGui::EndGroup();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Textures"))
		{
			ImGui::BeginGroup();

			if (ImGui::TreeNode("SomeFolder"))
			{
				ImGui::Text("Some Texture A");
				ImGui::Text("Some Texture B");
				ImGui::Text("Some Texture C");
				ImGui::TreePop();
			}

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::Text("Preview");
			ImGui::EndGroup();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Materials"))
		{
			ImGui::BeginGroup();

			if (ImGui::TreeNode("SomeFolder"))
			{
				ImGui::Text("Some Material A");
				ImGui::Text("Some Material B");
				ImGui::Text("Some Material C");
				ImGui::TreePop();
			}

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::Text("Preview");
			ImGui::EndGroup();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Shaders"))
		{
			ImGui::BeginGroup();

			if (ImGui::TreeNode("SomeFolder"))
			{
				ImGui::Text("Some Shader A");
				ImGui::Text("Some Shader B");
				ImGui::Text("Some Shader C");
				ImGui::TreePop();
			}

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::Text("Preview");
			ImGui::EndGroup();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Sounds"))
		{
			ImGui::BeginGroup();

			if (ImGui::TreeNode("SomeFolder"))
			{
				ImGui::Text("Some Sound A");
				ImGui::Text("Some Sound B");
				ImGui::Text("Some Sound C");
				ImGui::TreePop();
			}

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::Text("Preview");
			ImGui::EndGroup();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Music"))
		{
			ImGui::BeginGroup();

			if (ImGui::TreeNode("SomeFolder"))
			{
				ImGui::Text("Some Music A");
				ImGui::Text("Some Music B");
				ImGui::Text("Some Music C");
				ImGui::TreePop();
			}

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::Text("Preview");
			ImGui::EndGroup();
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::EndChild();

	ImGui::EndGroup();
}
