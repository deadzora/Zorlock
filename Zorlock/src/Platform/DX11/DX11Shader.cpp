#include "ZLpch.h"
#include "DX11Shader.h"
#include "DX11Raz.h"
#include "DX11Shaders.h"

namespace Zorlock
{
	enum class shaderType
	{
		VertexShader,
		PixelShader,
		ComputeShader,
		Unknown
	};


	static shaderType DXShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return shaderType::VertexShader;
		if (type == "fragment" || type == "pixel")
			return shaderType::PixelShader;
		if (type == "compute")
			return shaderType::ComputeShader;
		ZL_CORE_ASSERT(false, "Unknown shader type!");
		return shaderType::Unknown;
	}

	DX11Shader::DX11Shader() : m_RendererID(0)
	{
		m_RendererID = DX11Raz::RazCreateShader();
	}

	DX11Shader::DX11Shader(const std::string& filepath)
	{
		m_RendererID = DX11Raz::RazCreateShader();
		//oof 
		ZL_PROFILE_FUNCTION();
	}

	DX11Shader::DX11Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_Name(name)
	{
		ZL_PROFILE_FUNCTION();
	}

	DX11Shader::~DX11Shader()
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::Bind() const
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::Unbind() const
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::SetInt(const std::string& name, int value)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::SetFloat(const std::string& name, float value)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::UploadUniformInt(const std::string& name, int value)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::UploadUniformFloat(const std::string& name, float value)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Shader::UploadUniformBuffer(void* bufferblob)
	{
	}

	std::string DX11Shader::ReadFile(const std::string& filepath)
	{
		ZL_PROFILE_FUNCTION();
		return std::string();
	}

	void DX11Shader::Compile(const std::string shaderSources)
	{
	}




}
