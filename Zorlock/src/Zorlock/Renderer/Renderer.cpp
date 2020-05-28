#include "ZLpch.h"
#include "Zorlock/Renderer/Renderer.h"
#include "Zorlock/Renderer/Renderer2D.h"
#include "Zorlock/Game/SceneManager.h"

namespace Zorlock {

	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		ZL_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		RenderCommand::ReleaseRenderAPI();
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(Camera& camera)
	{	
		s_SceneData->ViewProjectionMatrix = camera.GetProjectionMatrix();//(camera.GetViewMatrix() * camera.GetProjectionMatrix());
		s_SceneData->ViewMatrix = camera.GetViewMatrix();
	}

	void Renderer::BeginScene()
	{
		s_SceneData->ViewProjectionMatrix = ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera()->GetProjectionMatrix();
		s_SceneData->ViewMatrix = ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera()->GetViewMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::RenderScene()
	{
		//use scenemanager here to handle rendering the scene
		ZLSCENEMANAGER::GetInstance()->GetActiveScene()->Render();
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const MATRIX4& transform)
	{
		shader->Bind();
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OpenGL:
		{
			shader->SetMat4("u_Transform", s_SceneData->ViewProjectionMatrix * s_SceneData->ViewMatrix * transform);

			break;
		}
		case RendererAPI::API::DX11:
		{
			shader->SetMat4("u_Transform", s_SceneData->ViewProjectionMatrix * s_SceneData->ViewMatrix * transform);
			break;
		}
		}
		
		shader->Apply();
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}