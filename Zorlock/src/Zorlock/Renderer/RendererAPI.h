#pragma once
#include "Zorlock/Renderer/VertexArray.h"
#include "Color.h"
namespace Zorlock {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, DX11 = 2
		};
	public:
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void SetClearColor(const COLOR4& color) = 0;
		virtual void Clear() = 0;
		virtual void Release() = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};




}

#define ZINT(v) (Zorlock::RendererAPI::GetAPI()==Zorlock::RendererAPI::API::OpenGL) ? v : (UINT)v
#define DXSHADERFILE(s) std::wstring(s.begin(), s.end()).c_str()
#define OPENGLSHADERFILE(s) s
#define SHADERFILE(s) (Zorlock::RendererAPI::GetAPI()==Zorlock::RendererAPI::API::OpenGL) ? OPENGLSHADERFILE(s) : DXSHADERFILE(s)
