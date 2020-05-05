#pragma once

#include "RenderCommand.h"
#include "Buffer.h"
#include "OrthographicCamera.h"
#include "Shader.h"


namespace Zorlock {


	class Renderer
	{
	public:
		struct SceneData
		{
			//this needs to be changed to use a GFX agnostic math
			glm::mat4 u_ViewProjection;
		};


		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		static void SetSceneData(void* data);

		


		static SceneData* GetSceneData();
	private:


		static SceneData* m_SceneData;

	};


}