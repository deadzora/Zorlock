#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace Zorlock {


	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		static void SetSceneData(void* data);

		struct SceneData
		{
			//this needs to be changed to use a GFX agnostic math
			glm::mat4 ViewProjectionMatrix;
		};
	private:


		static SceneData* m_SceneData;

	};


}