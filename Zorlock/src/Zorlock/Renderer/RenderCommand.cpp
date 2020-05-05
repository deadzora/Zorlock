#include "ZLpch.h"
#include "Zorlock/Renderer/RenderCommand.h"

namespace Zorlock {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}