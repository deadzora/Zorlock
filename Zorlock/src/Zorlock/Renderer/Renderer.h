#pragma once

#include "Zorlock/Renderer/RenderCommand.h"
#include "Zorlock/Renderer/OrthographicCamera.h"
#include "Zorlock/Renderer/Shader.h"

namespace Zorlock {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		
		static void OnWindowResize(uint32_t width, uint32_t height);
		//Soon use
		//static void BeginScene(Camera& camera);
		ZL_DEPRECATED("Rolling out new base Camera class")
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const MATRIX4& transform = MATRIX4().IDENTITY());

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			MATRIX4 ViewProjectionMatrix;
			MATRIX4 ViewMatrix;
		};
	public:
		ZL_DEPRECATED("Rolling out new SceneRenderer")
		static Scope<SceneData> s_SceneData;
	};


}
