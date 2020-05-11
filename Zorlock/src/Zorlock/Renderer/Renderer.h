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

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
	public:
		ZL_DEPRECATED("Rolling out new SceneRenderer")
		static Scope<SceneData> s_SceneData;
	};

#ifdef ZL_PLATFORM_WINDOWS
	//auto i = (float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - std::chrono::steady_clock::now()).count();
#define GETTIME (Renderer::GetAPI() == RendererAPI::API::DX11) ? (float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - std::chrono::steady_clock::now()).count() : (float)glfwGetTime()
#endif
}
