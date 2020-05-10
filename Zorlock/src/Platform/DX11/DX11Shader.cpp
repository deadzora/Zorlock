#include "ZLpch.h"
#include "DX11Shader.h"
#include "DX11Raz.h"
#include "DX11Shaders.h"
#include "DX11RendererAPI.h"

namespace Zorlock
{
	enum class shaderType
	{
		VertexShader = 0,
		PixelShader = 1,
		ComputeShader = 2,
		Geometry = 3,
		Hull = 4,
		Unknown = 5
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
		ZL_PROFILE_FUNCTION();
		m_RendererID = DX11Raz::RazCreateShader();

		//If we are compiling from file path then vsmain and psmain should be int he same file therefore we can pass it to both shaders
		m_RendererID->InitVertex(DXSHADERFILE(filepath));
		m_RendererID->InitPixel(DXSHADERFILE(filepath));

	}

	DX11Shader::DX11Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_Name(name)
	{
		ZL_PROFILE_FUNCTION();
		m_RendererID->InitVertex(vertexSrc);
		m_RendererID->InitPixel(fragmentSrc);
	}

	DX11Shader::~DX11Shader()
	{
		ZL_PROFILE_FUNCTION();
		m_RendererID->Release();
	}

	void DX11Shader::Bind() const
	{
		ZL_PROFILE_FUNCTION();
		//Use this to pass uniformbuffers
	}

	void DX11Shader::Unbind() const
	{
		ZL_PROFILE_FUNCTION();
		//no
	}

	void DX11Shader::Apply() const
	{
		m_RendererID->ApplyAllVertexCB();
		m_RendererID->ApplyAllPixelCB();
	}

	void DX11Shader::SetInt(const std::string& name, int value)
	{
		/*
		if (sizeof(int) % 16)
		{
			shaderData.push_back(static_cast<void*>(&value));
		}
		*/
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


	










}
