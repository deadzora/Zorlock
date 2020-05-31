#pragma once
#include "Zorlock/Renderer/RenderCommand.h"
#include "Zorlock/Game/SceneManager.h"
#include "Zorlock/Renderer/Shader.h"

#define ZLRENDERER Zorlock::Renderer

namespace Zorlock {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		
		static void OnWindowResize(uint32_t width, uint32_t height);
		//Soon use
		//static void BeginScene(Camera& camera);

		static void BeginScene(Camera& camera);
		static void BeginScene(Ref<Camera> camera);
		static void BeginScene(Ref<SceneManager> scenemanager);
		static void BeginScene();
		static void EndScene();
		static void RenderScene();
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const MATRIX4& transform = MATRIX4().IDENTITY());

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			MATRIX4 ViewProjectionMatrix;
			MATRIX4 ViewMatrix;
			VECTOR4 Ambient;
			VECTOR4 CamPosition;
		};
	public:

		static Scope<SceneData> s_SceneData;
	};


}
