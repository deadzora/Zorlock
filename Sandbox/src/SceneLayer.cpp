#include "SceneLayer.h"
#include "Zorlock/Game/SceneManager.h"
#include "Zorlock/Components/MeshRenderer.h"
#include "Zorlock/Renderer/Mesh.h"

#include "imgui/imgui.h"

SceneLayer::SceneLayer()
{
	ZLREF<ZLSCENEMANAGER> scenemanager = ZLSCENEMANAGER::GetInstance();
	ZLREF<ZLSCENE> nscene = scenemanager->CreateScene("Main Scene");
	m_mainScene= nscene;
	ZLREF<ZLSHADER> standard = ZLSHADERLIBRARY::GetInstance()->GetStandard();
	standard->Bind();
	ZLREF<ZLCAMERA> camera = ZLCREATECAMERA(FOV, AspectRatio, nearZ, farZ)
	mainCam = camera;
	mainmodel = m_mainScene->CreateGameObject("Model");
	ZLREF<ZLMESHRENDERER> meshrenderer = mainmodel->CreateComponent<Zorlock::MeshRenderer>();
	meshrenderer->AddModel("spaceship","assets/models/Woman_OBJ.obj");	
	m_meshrenderer = meshrenderer;
	m_Texture = Zorlock::Texture2D::Create("assets/textures/SciFi_Fighter.png");
	ZLREF<ZLMATERIAL> mat = meshrenderer->GetMaterial(0);
	mat->sharedTexture = m_Texture;




	//TEXTURE Shader
	textureShader = Zorlock::Shader::Create("Texture", "assets/shaders/TextureSingle.zlsl");
	textureShader->Bind();
	m_SquareVA = Zorlock::VertexArray::Create();
	float squareVertices[6 * 4] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f
	};
	Zorlock::Ref<Zorlock::VertexBuffer> squareVB = Zorlock::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout(textureShader->GetLayout(), textureShader.get());
	m_SquareVA->AddVertexBuffer(squareVB);
	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Zorlock::Ref<Zorlock::IndexBuffer> squareIB = Zorlock::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_ChernoLogoTexture = Zorlock::Texture2D::Create("assets/textures/ChernoLogo.png");
	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);

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
	rotation += ts * 1.0f;
	ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Update(ts);
	mainCam->transform->rotation = QUATERNION::EulerAngles(VECTOR3(0, rotation, 0));
	mainCam->transform->position.z = -rotation;
	mainCam->UpdateViewMatrix();



	ZLRENDERER::RenderScene();


	textureShader->Bind();
	m_ChernoLogoTexture->Bind();
	Zorlock::Renderer::Submit(textureShader, m_SquareVA, MATRIX4::TRS(VECTOR3(0.5, 0, 0.0f), QUATERNION::EulerAngles(VECTOR3(0, 0, 0)), VECTOR3(1.5f, 1.5f, 1.5f)));




	
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
