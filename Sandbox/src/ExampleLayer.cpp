#include "ExampleLayer.h"
#include "imgui/imgui.h"



ExampleLayer::ExampleLayer() 
	: Layer("ExampleLayer"), m_CameraController(1280.0f / 720.0f)
{
	m_FlatColorShader = Zorlock::Shader::Create("FlatColor", "assets/shaders/FlatColor.zlsl");
	textureShader = Zorlock::Shader::Create("Texture", "assets/shaders/TextureSingle.zlsl");
	//Load Shaders
	m_Shader = Zorlock::Shader::Create("VertexPosColor", "assets/shaders/VertexPosColor.zlsl");
	m_Shader->Bind();
	m_VertexArray = Zorlock::VertexArray::Create();
	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};
	Zorlock::Ref<Zorlock::VertexBuffer> vertexBuffer = Zorlock::VertexBuffer::Create(vertices, sizeof(vertices));
	m_Shader->Bind();
	vertexBuffer->SetLayout(m_Shader->GetLayout(), m_Shader.get());
	m_VertexArray->AddVertexBuffer(vertexBuffer);
	uint32_t indices[3] = { 0, 1, 2 };
	Zorlock::Ref<Zorlock::IndexBuffer> indexBuffer = Zorlock::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);
	m_SquareVA = Zorlock::VertexArray::Create();
	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	textureShader->Bind();
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

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor.ToVector3());

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			VECTOR3 pos(x * 0.11f, y * 0.11f, -0.15f);
			MATRIX4 transform = MATRIX4::TRS(pos,QUATERNION::IDENTITY(), VECTOR3(0.1f, 0.1f, 0.1f));
			Zorlock::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}

	textureShader->Bind();
	m_Texture->Bind();
	Zorlock::Renderer::Submit(textureShader, m_SquareVA, MATRIX4::TRS(Vector3(0,0,-0.125f),QUATERNION::IDENTITY(),VECTOR3(1.5f, 1.5f, 1.5f)));
	m_ChernoLogoTexture->Bind();
	Zorlock::Renderer::Submit(textureShader, m_SquareVA, MATRIX4::TRS(Vector3(0.5,0,-0.1f), QUATERNION::IDENTITY(), VECTOR3(1.5f, 1.5f, 1.5f)));



	// Triangle
	m_Shader->Bind();
	Zorlock::Renderer::Submit(m_Shader, m_VertexArray, MATRIX4::TRS(Vector3(0, 0, 0), QUATERNION::IDENTITY(), VECTOR3(1.0f, 1.0f, 1.0f)));

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
