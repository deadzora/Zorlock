#include "ZLpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Zorlock {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}