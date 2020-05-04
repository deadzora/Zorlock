#pragma once
#include "Zorlock/Renderer/Renderer.h"
#include <string>

//#include <glm/glm.hpp>

namespace Zorlock
{
	class Shader
	{
	public:
		Shader();
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {};
		~Shader() {};

		virtual void Bind() const {};
		virtual void Unbind() const {};
		void* GetRenderID() {
			return m_RendererID;
		};
		virtual void UploadUniforms(void * scene) {};
		

	protected:
		//i assume programID in openGL is the same as the Bufferslot in DX11.. maybe?
		//uint32_t m_RendererID;
		void* m_RendererID = nullptr;
	};
}