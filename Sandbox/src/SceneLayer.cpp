#include "SceneLayer.h"
#include "Zorlock/Game/SceneManager.h"
#include "Zorlock/Renderer/Mesh.h"
#include "imgui/imgui.h"

SceneLayer::SceneLayer() : Layer("Scene Layer"), m_CameraController(1280.0f / 720.0f), m_SquareColor(0.2f, 0.3f, 0.8f, 1.0f)
{
	ZL_PROFILE_FUNCTION();
	ZLREF<ZLSCENEMANAGER> scenemanager = ZLSCENEMANAGER::GetInstance();
	ZLREF<ZLSCENE> nscene = scenemanager->CreateScene("Main Scene");
	m_mainScene = nscene;
	ZLREF<ZLSHADER> standard = ZLSHADERLIBRARY::GetInstance()->GetStandard();
	standard->Bind();
	m_Texture = Zorlock::Texture2D::Create("assets/textures/SciFi_Fighter.png");
	//m_Texture = Zorlock::Texture2D::Create("assets/textures/crate.png");
	m_Texture->Bind();
	standard->SetInt("u_Texture", 0);
	ZLREF<ZLCAMERA> camera = ZLSCENEMANAGER::GetInstance()->GetActiveScene()->CreateCamera(FOV, AspectRatio, nearZ, farZ);
	mainCam = camera;
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->SetMainCamera(mainCam);
	mainmodel = m_mainScene->CreateGameObject("Model");
	ZLREF<ZLMESHRENDERER> meshrenderer = mainmodel->CreateComponent<Zorlock::MeshRenderer>();
	standard->Bind();
	//Uncomment a model to view it
	//meshrenderer->CreateQuad();	
	//meshrenderer->CreateCylinder(32);
	//meshrenderer->CreateCone(32);
	//meshrenderer->CreateSphere(32);
	//meshrenderer->CreateCube();
	//meshrenderer->AddModel("woman","assets/models/Woman_OBJ.obj");
	meshrenderer->AddModel("spaceship", "assets/models/MK6_OBJ.obj");
	m_meshrenderer = meshrenderer;

	ZLREF<ZLMATERIAL> mat = meshrenderer->GetMaterial(0);
	mat->sharedTexture = m_Texture;
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Awake();
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Start();

	m_CheckerboardTexture = Zorlock::Texture2D::Create("assets/textures/Checkerboard.png");

}
void SceneLayer::OnAttach()
{

}
void SceneLayer::OnDetach()
{
	ZL_PROFILE_FUNCTION();
}
void SceneLayer::OnUpdate(ZLTIME ts)
{
	ZL_PROFILE_FUNCTION();
	ZLRENDERCOMMAND::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });	
	ZLRENDERCOMMAND::Clear();


	ZLRENDERER::BeginScene(*mainCam.get());
	static float rotation = 0.0f;
	rotation += ts * 50.0f;
	mainmodel->transform->rotation = QUATERNION::EulerAngles(VECTOR3(0, rotation,0));
	mainmodel->transform->position.z = 10.0f;
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Update(ts);
	mainCam->transform->position.z = -10.0f;
	//mainCam->transform->rotation = QUATERNION::EulerAngles(VECTOR3(0, rotation, 0));
	mainCam->UpdateViewMatrix();
	ZLRENDERER::RenderScene();

	///////BEGIN 2D
	/*
	m_CameraController.OnUpdate(ts);
	ZLRENDER2D::ResetStats();	
	ZL_PROFILE_SCOPE("Renderer 2D Draw");
	ZLRENDER2D::BeginScene(m_CameraController.GetCamera());
	Zorlock::Renderer2D::DrawRotatedQuad(VECTOR2(1.0f, 0.0f), VECTOR2(0.8f, 0.8f), -45.0f, COLOR4(0.8f, 0.2f, 0.3f, 1.0f));
	Zorlock::Renderer2D::DrawQuad(VECTOR2(-1.0f, 0.0f), VECTOR2(0.8f, 0.8f), COLOR4(0.8f, 0.2f, 0.3f, 1.0f));
	Zorlock::Renderer2D::DrawQuad(VECTOR2(0.5f, -0.5f), VECTOR2(0.5f, 0.75f), m_SquareColor);
	Zorlock::Renderer2D::DrawQuad(VECTOR3(0.0f, 0.0f, -0.2f), VECTOR2(20.0f, 20.0f), m_CheckerboardTexture, 10.0f);
	Zorlock::Renderer2D::DrawRotatedQuad(VECTOR3(-2.0f, 0.0f, -0.005f), VECTOR2(1.0f, 1.0f), rotation, m_CheckerboardTexture, 20.0f);
	ZLRENDER2D::EndScene();	
	*/
}


void SceneLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("Testing");
	ImGui::End();
}
void SceneLayer::OnEvent(ZLEVENT& e)
{
	m_CameraController.OnEvent(e);
}
