#include "SceneLayer.h"
#include "Zorlock/Game/SceneManager.h"
#include "Zorlock/Renderer/Environment.h"
#include "Zorlock/Renderer/Mesh.h"
#include "imgui/imgui.h"

SceneLayer::SceneLayer() : Layer("Scene Layer"), m_CameraController(1280.0f / 720.0f), m_SquareColor(0.2f, 0.3f, 0.8f, 1.0f)
{
	ZL_PROFILE_FUNCTION();

	//////GET SCENEMANAGER
	ZLREF<ZLSCENEMANAGER> scenemanager = ZLSCENEMANAGER::GetInstance();
	ZLREF<ZLSCENE> nscene = scenemanager->CreateScene("Main Scene");
	m_mainScene = nscene;
	m_mainScene->GetEnvironment()->SetAmbient(COLOR4::BLACK());
	//////GET STANDARD SHADER - soon this won't be neccesary
	ZLREF<ZLSHADER> standard = ZLSHADERLIBRARY::GetInstance()->GetStandard();
	standard->Bind();

	//////LOAD SHIP TEXTURE
	m_Texture = Zorlock::Texture2D::Create("assets/textures/SciFi_Fighter.png");
	//////CRATE TEXTURE
	//m_Texture = Zorlock::Texture2D::Create("assets/textures/crate.png");
	m_Texture->Bind();
	standard->SetInt("u_Texture", 0);


	//////CAMERA
	ZLREF<ZLCAMERA> camera = ZLSCENEMANAGER::GetInstance()->GetActiveScene()->CreateCamera(FOV, AspectRatio, nearZ, farZ);
	mainCam = camera;
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->SetMainCamera(mainCam);
	mainCam->transform->position.z = -10.0f;

	///////LIGHTA
	lightA = ZLSCENEMANAGER::GetInstance()->GetActiveScene()->CreateLight();
	lightA->transform->position = VECTOR3(10, 0, 10);
	lightA->SetColor(COLOR4(0, 1, 0, 1));
	lightA->SetStrength(1.15);
	lightA->SetRadius(50);


	///////LIGHTB
	lightB = ZLSCENEMANAGER::GetInstance()->GetActiveScene()->CreateLight();
	lightB->transform->position = VECTOR3(-10, 0, 10);
	lightB->SetColor(COLOR4(1, 0, 0, 1));
	lightB->SetStrength(0.65);
	lightB->SetRadius(60);

	///////LIGHTC
	lightC = ZLSCENEMANAGER::GetInstance()->GetActiveScene()->CreateLight();
	lightC->transform->position = VECTOR3(0, 0, 5);
	lightC->SetColor(COLOR4(0, 0, 1, 1));
	lightC->SetStrength(0.75);
	lightC->SetRadius(60);

	//////MAIN GAME OBJECT
	mainmodel = m_mainScene->CreateGameObject("Model");
	ZLREF<ZLMESHRENDERER> meshrenderer = mainmodel->CreateComponent<Zorlock::MeshRenderer>();
	standard->Bind();

	//////CHOOSE MODEL TO VIEW - UNCOMMENT
	//meshrenderer->CreateQuad();	
	//meshrenderer->CreateCylinder(32);
	//meshrenderer->CreateCone(32);
	//meshrenderer->CreateSphere(32);
	//meshrenderer->CreateCube();
	//meshrenderer->AddModel("woman","assets/models/Woman_OBJ.obj");
	meshrenderer->AddModel("spaceship", "assets/models/MK6_OBJ.obj");
	m_meshrenderer = meshrenderer;
	mainmodel->transform->position.z = 10.0f;

	///////MATERIAL SETTINGS
	ZLREF<ZLMATERIAL> mat = meshrenderer->GetMaterial(0);
	mat->sharedTexture = m_Texture;
	mat->SetShininess(32);
	mat->SetSpecular(0.1f);
	///////SEND AWAKE METHOD TO CHILDREN
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Awake();
	

	m_CheckerboardTexture = Zorlock::Texture2D::Create("assets/textures/Checkerboard.png");

}
void SceneLayer::OnAttach()
{
	///////SEND START METHOD TO CHILDREN
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Start();
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
	ZLRENDERER::BeginScene();

	static float rotation = 0.0f;
	rotation += ts * 50.0f;
	mainmodel->transform->rotation = QUATERNION::EulerAngles(VECTOR3(0, rotation, 0));

	
	

	///////UPDATE SCENE MATRIX AND CHILDREN
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Update(ts);
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
	m_CameraController.OnEvent(e);
}
