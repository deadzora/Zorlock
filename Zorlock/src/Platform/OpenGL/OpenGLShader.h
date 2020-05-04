#pragma once
#include "Zorlock/Renderer/Shader.h"
#include <string>
#include <glm/glm.hpp>

namespace Zorlock
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void UploadUniforms(void* scene) override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:

		
	};
}