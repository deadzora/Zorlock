#pragma once

//No we should not have openGL stuff in an agnostic renderer
//#include <glm/glm.hpp>
#include "ZColor.h"
#include "VertexArray.h"

namespace Zorlock {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, DX11 = 2
		};
	public:
		virtual void SetClearColor(const ZColor color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;



		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;

	public:



	};

}