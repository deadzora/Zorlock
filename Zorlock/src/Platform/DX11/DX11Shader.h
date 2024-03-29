#pragma once
#include "Zorlock/Renderer/Shader.h"
#include <d3d11.h>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace DX11Raz {
	class RazShader;
}



namespace Zorlock {

	class Texture2D;

	class DX11Shader : public Shader
	{
	public:
		DX11Shader();
		DX11Shader(const std::string& filepath);
		DX11Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		DX11Shader(const std::string& name, const std::string& filepath);
		DX11Shader(const std::string& source, bool diff);
		virtual ~DX11Shader() override;
		
		virtual void Bind() const override;
		virtual void Unbind() const override;
		ZL_DEPRECATED("No longer need this for DX11")
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
		virtual void PostProcess() override;
		virtual void* GetShaderID() const override;
		virtual const std::string GetName() const override { return m_Name; }
		void Compile(std::string vertexshadersource, std::string pixelshadersource);

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);
		void UploadUniformDataArray(const std::string& name, void* values, uint32_t count);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const VECTOR2& value);
		void UploadUniformFloat3(const std::string& name, const VECTOR3& value);
		void UploadUniformFloat4(const std::string& name, const VECTOR4& value);
		void UploadUniformMat3(const std::string& name, const MATRIX3& matrix);
		void UploadUniformMat4(const std::string& name, const MATRIX4& matrix);
		void UploadUniformBuffer(const std::string& name, const void* buffer, uint32_t size, uint32_t count);
		Ref<DX11Raz::RazShader> GetShader()
		{
			return m_RendererID;
		}

		

	private:

		Ref<DX11Raz::RazShader> m_RendererID;
		std::string m_Name;
	};



}