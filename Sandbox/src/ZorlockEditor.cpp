#include "ZorlockEditor.h"
#include "Zorlock/Game/SceneManager.h"
#include "Zorlock/Renderer/Environment.h"
#include "Zorlock/Editor/EditorUI.h"
#include "Zorlock/ImGui/ImGuiSkins.h"

ZorlockEditor::ZorlockEditor() : Layer("Scene Layer"), m_CameraController(1280.0f / 720.0f)
{
	//////GET SCENEMANAGER
	ZLSETFONT
	ZLIMGUIALPHA(0.9f)
	ZLIMGUITWILIGHT
	ZLREF<ZLSCENEMANAGER> scenemanager = ZLSCENEMANAGER::GetInstance();
	ZLREF<ZLSCENE> nscene = scenemanager->CreateScene("Main Scene");
	m_mainScene = nscene;
	m_mainScene->GetEnvironment()->SetAmbient(COLOR4::BLACK());
	ZLREF<ZLSHADER> standard = ZLSHADERLIBRARY::GetInstance()->GetStandard();
	standard->Bind();

	ZLREF<ZLCAMERA> camera = ZLSCENEMANAGER::GetInstance()->GetActiveScene()->CreateCamera(FOV, AspectRatio, nearZ, farZ);
	mainCam = camera;
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->SetMainCamera(mainCam);
	mainCam->transform->position.z = -20.0f;
	mainCam->transform->position.y = -5.0f;

	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Awake();

	
	appready = true;
}

void ZorlockEditor::OnAttach()
{
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Start();
}

void ZorlockEditor::OnDetach()
{
}

void ZorlockEditor::OnUpdate(ZLTIME ts)
{
	ZL_PROFILE_FUNCTION();
	ZLRENDERCOMMAND::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	ZLRENDERCOMMAND::Clear();
	ZLRENDERER::BeginScene();

	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Update(ts);

	ZLRENDERER::RenderScene();
}

void ZorlockEditor::OnImGuiRender()
{
	if (appready == true)
	{
		ZLEDITORUI::Get()->EditorUIDraw();
	}
}

void ZorlockEditor::OnEvent(ZLEVENT& e)
{
	m_CameraController.OnEvent(e);
}


