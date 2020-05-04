#pragma once

#include "Zorlock/Renderer/RendererAPI.h"

namespace Zorlock {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const ZColor color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};


}