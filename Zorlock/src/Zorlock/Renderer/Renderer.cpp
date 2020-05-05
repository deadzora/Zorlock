#include "ZLpch.h"
#include "Renderer.h"

namespace Zorlock {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		//Normally here you would pass the camera view matrix and projection matrix down into each renderable object in the scene and update their shaders
		//with the matrix info, but since we are just going to use a global uniformbuffer (constantbuffer) we will just bind this to the main scene shader.


		m_SceneData->u_ViewProjection = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)

	{
		//globalbuffer->UpdateData(Renderer::m_SceneData);
		//shader->UploadUniforms(m_SceneData);
		shader->Bind();
		//globalbuffer->Bind(shader->GetRenderID);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::SetSceneData(void* data)
	{

	}

	Renderer::SceneData* Renderer::GetSceneData()
	{
		return m_SceneData;
	}

}