#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Zorlock
{
	class Shader
	{
	public:
		Shader() {};
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	protected:
		uint32_t m_RendererID;
	};
}