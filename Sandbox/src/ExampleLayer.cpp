#include "ExampleLayer.h"
#include "imgui/imgui.h"



ExampleLayer::ExampleLayer() 
	: Layer("ExampleLayer"), m_CameraController(1280.0f / 720.0f)
{
	m_FlatColorShader = Zorlock::Shader::Create("FlatColor", "assets/shaders/FlatColor.zlsl");


	//VERTEX POS Shader
	m_Shader = Zorlock::Shader::Create("VertexPosColor", "assets/shaders/VertexPosColor.zlsl");
	m_Shader->Bind();
	m_VertexArray = Zorlock::VertexArray::Create();
	float vertices[3 * 8] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 1.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};
	Zorlock::Ref<Zorlock::VertexBuffer> vertexBuffer = Zorlock::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexBuffer->SetLayout(m_Shader->GetLayout(), m_Shader.get());
	m_VertexArray->AddVertexBuffer(vertexBuffer);
	uint32_t indices[3] = { 0, 1, 2 };
	Zorlock::Ref<Zorlock::IndexBuffer> indexBuffer = Zorlock::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);


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


	m_Texture = Zorlock::Texture2D::Create("assets/textures/Checkerboard.png");
	m_ChernoLogoTexture = Zorlock::Texture2D::Create("assets/textures/ChernoLogo.png");
	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Zorlock::Timestep ts) 
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Zorlock::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Zorlock::RenderCommand::Clear();

	Zorlock::Renderer::BeginScene(m_CameraController.GetCamera());

	//MATRIX4 scale = MATRIX4::IDENTITY() * MATRIX4::scaling(VECTOR3(0.1f, 0.1f, 0.1f)); //glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


	textureShader->Bind();
	m_Texture->Bind();
	Zorlock::Renderer::Submit(textureShader, m_SquareVA, MATRIX4::TRS(Vector3(0,0,-0.125f), QUATERNION::EulerAngles(VECTOR3(0, 0, 0)),VECTOR3(1.5f, 1.5f, 1.5f)));
	m_ChernoLogoTexture->Bind();
	Zorlock::Renderer::Submit(textureShader, m_SquareVA, MATRIX4::TRS(Vector3(0.5f,0,-0.1f), QUATERNION::EulerAngles(VECTOR3(0, 0, 0)), VECTOR3(1.5f, 1.5f, 1.5f)));



	// Triangle
	m_Shader->Bind();
	Zorlock::Renderer::Submit(m_Shader, m_VertexArray,  MATRIX4::TRS(Vector3(0, 0, -0.05f), QUATERNION::EulerAngles(VECTOR3(0, 0, 0)), VECTOR3(1.0f, 1.0f, 1.0f)));
	Zorlock::Renderer::EndScene();

	//ZL_CORE_TRACE("Renderer Loaded");
}

void ExampleLayer::OnImGuiRender() 
{
	//ZL_CORE_TRACE("ImGui Loading");
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", &m_SquareColor.x);
	ImGui::End();
}

void ExampleLayer::OnEvent(Zorlock::Event& e) 
{
	m_CameraController.OnEvent(e);
}
