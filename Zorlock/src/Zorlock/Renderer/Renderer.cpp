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
		
		if (RendererAPI::GetAPI() == RendererAPI::API::DX11)
		{
			s_SceneData->ViewProjectionMatrix = (camera.GetViewMatrix() * camera.GetProjectionMatrix());
		}
		else {
			s_SceneData->ViewProjectionMatrix = (camera.GetProjectionMatrix() * camera.GetViewMatrix());
		}
	
		//s_SceneData->ViewProjectionMatrix = camera.GetProjectionMatrix();
		//s_SceneData->ViewMatrix = camera.GetViewMatrix();
	}

	void Renderer::BeginScene()
	{
		//Get main camera if none is supplied
		if (ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera())
		{
			if (RendererAPI::GetAPI() == RendererAPI::API::DX11)
			{
				s_SceneData->ViewProjectionMatrix = (ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera()->GetViewMatrix() * ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera()->GetProjectionMatrix());

			}
			else {
				s_SceneData->ViewProjectionMatrix = (ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera()->GetProjectionMatrix() * ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera()->GetViewMatrix());

			}

		}
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
		//shader->SetMat4("u_ViewMatrix", s_SceneData->ViewMatrix);
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);
		shader->Apply();
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}