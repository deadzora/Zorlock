#include "DX11Layer.h"
#include "imgui/imgui.h"



DX11Layer::DX11Layer() : Layer("DX11Layer"), m_CameraController(1280.0f / 720.0f)
{
	

	rotation = 0.0f;
	m_FlatColorShader = Zorlock::Shader::Create("FlatColor", "assets/shaders/FlatColor2.zlsl");
	//m_Shader = Zorlock::Shader::Create("VertexPosColor", "assets/shaders/VertexPosColor2.zlsl");
	m_SquareVA = Zorlock::VertexArray::Create();
	float squareVertices[4 * 4] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 
		 0.5f, -0.5f, 0.0f, 1.0f, 
		 0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 
	};
	m_FlatColorShader->Bind();
	Zorlock::Ref<Zorlock::VertexBuffer> squareVB = Zorlock::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout(m_FlatColorShader->GetLayout(), m_FlatColorShader.get());
	m_SquareVA->AddVertexBuffer(squareVB);
	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Zorlock::Ref<Zorlock::IndexBuffer> squareIB = Zorlock::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);
}

void DX11Layer::OnAttach()
{
}

void DX11Layer::OnDetach()
{
}

void DX11Layer::OnUpdate(Zorlock::Timestep ts)
{
	
	rotation += 0.5f;
	if (rotation >= 360) rotation = 0;
	m_CameraController.OnUpdate(ts);

	Zorlock::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Zorlock::RenderCommand::Clear();


	Zorlock::Renderer::BeginScene(m_CameraController.GetCamera());
	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor.ToVector3());

	for (float y = 0; y < 20; y++)
	{
		for (float x = 0; x < 20; x++)
		{
			VECTOR3 pos(x * 0.11f, y * 0.11f, -0.15f);
			MATRIX4 transform = MATRIX4::TRS(pos, QUATERNION::EulerAngles(VECTOR3(0,0,0)), VECTOR3(0.1f, 0.1f, 0.1f));
			Zorlock::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}



	Zorlock::Renderer::EndScene();
}

void DX11Layer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", &m_SquareColor.x);
	ImGui::Text("Rotation: %f", rotation);
	ImGui::End();
}

void DX11Layer::OnEvent(Zorlock::Event& e)
{
	m_CameraController.OnEvent(e);
}


