#include "SceneLayer.h"
#include "Zorlock/Game/SceneManager.h"
#include "Zorlock/Renderer/Mesh.h"
#include "imgui/imgui.h"

SceneLayer::SceneLayer()
{

	ZLREF<ZLSCENEMANAGER> scenemanager = ZLSCENEMANAGER::GetInstance();
	ZLREF<ZLSCENE> nscene = scenemanager->CreateScene("Main Scene");
	m_mainScene= nscene;
	ZLREF<ZLSHADER> standard = ZLSHADERLIBRARY::GetInstance()->GetStandard();
	standard->Bind();
	//m_Texture = Zorlock::Texture2D::Create("assets/textures/SciFi_Fighter.png");
	m_Texture = Zorlock::Texture2D::Create("assets/textures/crate.png");
	m_Texture->Bind();
	standard->SetInt("u_Texture", 0);
	ZLREF<ZLCAMERA> camera = ZLCREATECAMERA(FOV, AspectRatio, nearZ, farZ)
	mainCam = camera;
	mainmodel = m_mainScene->CreateGameObject("Model");
	ZLREF<ZLMESHRENDERER> meshrenderer = mainmodel->CreateComponent<Zorlock::MeshRenderer>();
	standard->Bind();
	//Uncomment a model to view it

	//meshrenderer->CreateQuad();	
	//meshrenderer->CreateCylinder(32);
	meshrenderer->CreateCone(32);
	//meshrenderer->CreateSphere(32);
	//meshrenderer->CreateCube();
	//meshrenderer->AddModel("woman","assets/models/Woman_OBJ.obj");
	//meshrenderer->AddModel("spaceship", "assets/models/MK6_OBJ.obj");
	m_meshrenderer = meshrenderer;	

	ZLREF<ZLMATERIAL> mat = meshrenderer->GetMaterial(0);
	mat->sharedTexture = m_Texture;
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Awake();
}
void SceneLayer::OnAttach()
{
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Start();
}
void SceneLayer::OnDetach()
{
}
void SceneLayer::OnUpdate(ZLTIME ts)
{
	//ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Update(ts);
	ZLRENDERCOMMAND::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });	
	ZLRENDERCOMMAND::Clear();
	ZLRENDERER::BeginScene();

	static float rotation = 0.0f;
	rotation += ts * 50.0f;

	mainmodel->transform->rotation = QUATERNION::EulerAngles(VECTOR3(0,rotation,180));
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Update(ts);

	mainCam->transform->position.z = -10.0f;
	mainCam->UpdateViewMatrix();



	ZLRENDERER::RenderScene();




	
}
void SceneLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("Testing");
	ImGui::End();
}
void SceneLayer::OnEvent(ZLEVENT& e)
{
}
