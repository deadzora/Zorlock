#include "ZLpch.h"
#include "Zorlock/Renderer/Renderer.h"
#include "Zorlock/Renderer/Renderer2D.h"
#include "Zorlock/Renderer/Environment.h"

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

	void Renderer::BeginScene(Ref<Camera> camera)
	{	
		s_SceneData->ViewProjectionMatrix = camera->GetProjectionMatrix();//(camera.GetViewMatrix() * camera.GetProjectionMatrix());
		s_SceneData->ViewMatrix = camera->GetViewMatrix();
	}

	void Renderer::BeginScene(Ref<SceneManager> scenemanager)
	{
		s_SceneData->ViewProjectionMatrix = scenemanager->GetActiveScene()->MainCamera()->GetProjectionMatrix();
		s_SceneData->ViewMatrix = scenemanager->GetActiveScene()->MainCamera()->GetViewMatrix();
		s_SceneData->Ambient = VECTOR4(scenemanager->GetActiveScene()->GetEnvironment()->GetAmbient());
	}

	void Renderer::BeginScene()
	{
		s_SceneData->ViewProjectionMatrix = ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera()->GetProjectionMatrix();
		s_SceneData->ViewMatrix = ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera()->GetViewMatrix();
		s_SceneData->Ambient = VECTOR4(ZLSCENEMANAGER::GetInstance()->GetActiveScene()->GetEnvironment()->GetAmbient());
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
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix * s_SceneData->ViewMatrix * transform);
		shader->SetMat4("u_Transform", transform);
		shader->SetFloat4("u_Ambient", s_SceneData->Ambient); //For light calculations		
		shader->Apply();
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}