#pragma once

#include "Zorlock/Renderer/Shader.h"
#include <glm/glm.hpp>
#include <map>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Zorlock {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader();
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& name, const std::string& filepath);
		OpenGLShader(const std::string& source, bool diff);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Apply() const override;
		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetTextureArray(const std::string& name, void* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		//virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat3(const std::string& name, const VECTOR3& value) override;
		//virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetFloat4(const std::string& name, const VECTOR4& value) override;
		//virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
		virtual void SetMat4(const std::string& name, const MATRIX4& value) override;
		virtual void SetBuffer(const std::string& name, const void* buffer, uint32_t size, uint32_t count) override;
		virtual void* GetShaderID() const override;
		void PostProcess() override;
		virtual const std::string GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);
		void UploadUniformDataArray(const std::string& name, void* values, uint32_t count);
		void UploadUniformFloat(const std::string& name, float value);
		//void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		//void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat2(const std::string& name, const VECTOR2& value);
		void UploadUniformFloat3(const std::string& name, const VECTOR3& value);
		//void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		void UploadUniformFloat4(const std::string& name, const VECTOR4& value);

		//void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformMat3(const std::string& name, const MATRIX3& matrix);
		void UploadUniformMat4(const std::string& name, const MATRIX4& matrix);
		void UploadUniformBuffer(const std::string& name, const void* buffer, uint32_t size, uint32_t count);
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		std::map<std::string, unsigned int> buffers;
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}