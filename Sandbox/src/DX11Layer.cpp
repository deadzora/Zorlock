#include "DX11Layer.h"
#include "imgui/imgui.h"
#include "Platform/DX11/DX11Shader.h"
#include <d3d11.h>
#include <DirectXMath.h>

struct ShaderDataA
{
	DirectX::XMMATRIX wvpMatrix;
	DirectX::XMMATRIX worldMatrix;
};

//ShaderDataA* World = new ShaderDataA();
UINT vbufferhandle;
UINT pbufferhandle;
Zorlock::DX11Shader * dxplaneshader;
DX11Layer::DX11Layer() : Layer("DX11Layer"), m_CameraController(1280.0f / 720.0f)
{
	m_VertexArray = Zorlock::VertexArray::Create();
	m_VertexArray->Bind();
	
	
	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	Zorlock::Ref<Zorlock::VertexBuffer> vertexBuffer = Zorlock::VertexBuffer::Create(vertices, sizeof(vertices));




	Zorlock::BufferLayout layout = {
	{ Zorlock::ShaderDataType::Float3, "position" },
	{ Zorlock::ShaderDataType::Float3, "texcoord" }
	};

	uint32_t indices[3] = { 0, 1, 2 };

	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);
	Zorlock::Ref<Zorlock::IndexBuffer> indexBuffer = Zorlock::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);








	auto planeshader = m_ShaderLibrary.Load("assets/shaders/shader2d.fx");
	//dxplaneshader = static_cast<Zorlock::DX11Shader*>(&planeshader.~shared_ptr);
	//vbufferhandle = dxplaneshader->CreateVertexBufferData<ShaderDataA>(World);
	//pbufferhandle = dxplaneshader->CreatePixelBufferData<ShaderDataA>(World);



	

}

void DX11Layer::OnAttach()
{
}

void DX11Layer::OnDetach()
{
}

void DX11Layer::OnUpdate(Zorlock::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Zorlock::RenderCommand::SetClearColor({ 0.1f, 1.0f, 1.0f, 1 });
	Zorlock::RenderCommand::Clear();

	Zorlock::Renderer::BeginScene(m_CameraController.GetCamera());


	//World->wvpMatrix = DirectX::XMMatrixIdentity(); //Zorlock::Renderer::s_SceneData->ViewProjectionMatrix;
	//World->worldMatrix = DirectX::XMMatrixIdentity(); //glm::mat4(1.0f);

	//dxplaneshader->SetVertexBufferData<ShaderDataA>(vbufferhandle);
	//dxplaneshader->SetPixelBufferData<ShaderDataA>(pbufferhandle);

	//dxplaneshader->Apply();

	Zorlock::Renderer::EndScene();
}

void DX11Layer::OnImGuiRender()
{
	ImGui::Begin("test");
	ImGui::Text("This is example text");
	ImGui::Button("Click Me!");
	ImGui::SameLine();
	std::string clickcount = "You're mom ";
	ImGui::Text(clickcount.c_str());
	ImGui::End();
}

void DX11Layer::OnEvent(Zorlock::Event& e)
{
}
