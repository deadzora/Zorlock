#include "ZLpch.h"
#include "DX11Shader.h"
#include "DX11Raz.h"
#include "DX11Shaders.h"
#include "DX11RendererAPI.h"
#include <ZLSLParser.h>
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

	DX11Shader::DX11Shader() : Shader(), m_RendererID(0)
	{
		CreateParser();
		m_RendererID = DX11Raz::RazCreateShader();
	}

	DX11Shader::DX11Shader(const std::string& filepath)  : Shader()
	{
		ZL_PROFILE_FUNCTION();
		m_RendererID = DX11Raz::RazCreateShader();

		//If we are compiling from file path then vsmain and psmain should be int he same file therefore we can pass it to both shaders
		m_RendererID->InitVertex(DXSHADERFILE(filepath));
		m_RendererID->InitPixel(DXSHADERFILE(filepath));

	}

	DX11Shader::DX11Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_Name(name), Shader()
	{

		m_RendererID = DX11Raz::RazCreateShader();
		Compile(vertexSrc, fragmentSrc);

	}

	DX11Shader::DX11Shader(const std::string& name, const std::string& filepath)
	{
		ZL_PROFILE_FUNCTION();
		CreateParser();
		parser->Parse(filepath);
		Process();
		printf("COMPILE SHADERS!! \n");
		std::string vertexSrc = parser->GetShader(Zorlock::ZLSLParser::OutPutShaderType::HLSL, Zorlock::ZLSLParser::ShaderSection::VERTEXSHADER);
		std::string fragmentSrc = parser->GetShader(Zorlock::ZLSLParser::OutPutShaderType::HLSL, Zorlock::ZLSLParser::ShaderSection::FRAGMENTSHADER);
		parser->SaveShader(vertexSrc, filepath + "_vertex.hlsl");
		parser->SaveShader(fragmentSrc, filepath + "_pixel.hlsl");
		m_RendererID = DX11Raz::RazCreateShader();
		Compile(vertexSrc, fragmentSrc);
	}

	DX11Shader::DX11Shader(const std::string& source, bool diff)
	{
		ZL_PROFILE_FUNCTION();
		CreateParser();
		parser->Parse(source);
		Process();
		printf("COMPILE SHADERS!! \n");
		std::string vertexSrc = parser->GetShader(Zorlock::ZLSLParser::OutPutShaderType::HLSL, Zorlock::ZLSLParser::ShaderSection::VERTEXSHADER);
		std::string fragmentSrc = parser->GetShader(Zorlock::ZLSLParser::OutPutShaderType::HLSL, Zorlock::ZLSLParser::ShaderSection::FRAGMENTSHADER);
		parser->SaveShader(vertexSrc, "_vertex.hlsl");
		parser->SaveShader(fragmentSrc, "_pixel.hlsl");
		m_RendererID = DX11Raz::RazCreateShader();
		Compile(vertexSrc, fragmentSrc);
	}

	DX11Shader::~DX11Shader()
	{
		ZL_PROFILE_FUNCTION();
		DX11Raz::RazDeleteShader(m_RendererID);
	}

	void DX11Shader::Bind() const
	{
		ZL_PROFILE_FUNCTION();
		DX11Raz::RazSetCurrentShader(m_RendererID);

	}

	void DX11Shader::Unbind() const
	{
		ZL_PROFILE_FUNCTION();
		DX11Raz::RazSetCurrentShader(0);
	}

	void DX11Shader::Apply() const
	{
		m_RendererID->ApplyAllVertexCB();
		m_RendererID->ApplyAllPixelCB();
	}

	void DX11Shader::SetInt(const std::string& name, int value)
	{

		ZL_PROFILE_FUNCTION();

		//figure out if this is pixelor vertex
		for (size_t i = 0; i < m_VUniformVars.size(); i++)
		{
			if (m_VUniformVars[i].Name.compare(name) == 0)
			{
				int p = value;
				m_RendererID->UpdateVertexCB(&p, name);
				m_RendererID->ApplyVertexCB(name);
				break;
			}
		}
		for (size_t i = 0; i < m_FUniformVars.size(); i++)
		{
			if (m_FUniformVars[i].Name.compare(name) == 0)
			{
				int p = value;
				m_RendererID->UpdatePixelCB(&p, name);
				m_RendererID->ApplyPixelCB(name);
				break;
			}
		}
	}

	void DX11Shader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{

	}

	void DX11Shader::SetFloat(const std::string& name, float value)
	{
		ZL_PROFILE_FUNCTION();

		//figure out if this is pixelor vertex
		for (size_t i = 0; i < m_VUniformVars.size(); i++)
		{
			if (m_VUniformVars[i].Name.compare(name) == 0)
			{
				float p = value;
				m_RendererID->UpdateVertexCB(&p, name);
				m_RendererID->ApplyVertexCB(name);
				break;
			}
		}
		for (size_t i = 0; i < m_FUniformVars.size(); i++)
		{
			if (m_FUniformVars[i].Name.compare(name) == 0)
			{
				float p = value;
				m_RendererID->UpdatePixelCB(&p, name);
				m_RendererID->ApplyPixelCB(name);
				break;
			}
		}
	}



	void DX11Shader::SetFloat3(const std::string& name, const VECTOR3& value)
	{


		//figure out if this is pixelor vertex
		for (size_t i = 0; i < m_VUniformVars.size(); i++)
		{
			if (m_VUniformVars[i].Name.compare(name) == 0)
			{
				VECTOR3 p = value;
				m_RendererID->UpdateVertexCB(&p, name);
				m_RendererID->ApplyVertexCB(name);
				break;
			}
		}
		for (size_t i = 0; i < m_FUniformVars.size(); i++)
		{
			if (m_FUniformVars[i].Name.compare(name) == 0)
			{
				VECTOR3 p = value;
				m_RendererID->UpdatePixelCB(&p, name);
				m_RendererID->ApplyPixelCB(name);
				break;
			}
		}

	}



	void DX11Shader::SetFloat4(const std::string& name, const VECTOR4& value)
	{

		//figure out if this is pixelor vertex
		for (size_t i = 0; i < m_VUniformVars.size(); i++)
		{
			if (m_VUniformVars[i].Name.compare(name) == 0)
			{
				VECTOR4 p = value;
				m_RendererID->UpdateVertexCB(&p, name);
				m_RendererID->ApplyVertexCB(name);
				break;
			}
		}
		for (size_t i = 0; i < m_FUniformVars.size(); i++)
		{
			if (m_FUniformVars[i].Name.compare(name) == 0)
			{
				VECTOR4 p = value;
				m_RendererID->UpdatePixelCB(&p, name);
				m_RendererID->ApplyPixelCB(name);
				break;
			}
		}

	}



	void DX11Shader::SetMat4(const std::string& name, const MATRIX4& value)
	{
		//figure out if this is pixelor vertex
		for (size_t i = 0; i < m_VUniformVars.size(); i++)
		{
			if (m_VUniformVars[i].Name.compare(name) == 0)
			{
				MATRIX4 p = value;
				//OutputDebugString(L" Setting Tansformation matrix\r\n");
				m_RendererID->UpdateVertexCB(p.To4x4Array(), name);
				m_RendererID->ApplyVertexCB(name);
				break;
			}
		}
		for (size_t i = 0; i < m_FUniformVars.size(); i++)
		{
			if (m_FUniformVars[i].Name.compare(name) == 0)
			{
				MATRIX4 p = value;
				m_RendererID->UpdatePixelCB(p.To4x4Array(), name);
				m_RendererID->ApplyPixelCB(name);
				break;
			}
		}


	}

	void DX11Shader::PostProcess()
	{

	}

	void* DX11Shader::GetShaderID() const
	{
		return (void*)m_RendererID;
	}

	void DX11Shader::Compile(std::string vertexshadersource, std::string pixelshadersource)
	{
		if (m_RendererID->InitVertex(vertexshadersource))
		{
			for (size_t i = 0; i < m_VUniformVars.size(); i++)
			{
				switch (m_VUniformVars[i].Type)
				{
				case ShaderDataType::Mat4:
				{
					printf("Uniform: %s on slot %i \n", m_VUniformVars[i].Name.c_str(), m_VUniformVars[i].Slot);
					m_RendererID->CreateVertexCB(m_VUniformVars[i].Name, m_VUniformVars[i].Slot, new MATRIX4(), sizeof(MATRIX4));
					break;
				}
				case ShaderDataType::Mat3:
				{
					m_RendererID->CreateVertexCB(m_VUniformVars[i].Name, m_VUniformVars[i].Slot, new MATRIX3(), sizeof(MATRIX3));
					break;
				}
				case ShaderDataType::Float4:
				{
					m_RendererID->CreateVertexCB(m_VUniformVars[i].Name, m_VUniformVars[i].Slot, new VECTOR4(), sizeof(VECTOR4));
					break;
				}
				case ShaderDataType::Float3:
				{
					m_RendererID->CreateVertexCB(m_VUniformVars[i].Name, m_VUniformVars[i].Slot, new VECTOR3(), sizeof(VECTOR3));
					break;
				}
				case ShaderDataType::Float2:
				{
					m_RendererID->CreateVertexCB(m_VUniformVars[i].Name, m_VUniformVars[i].Slot, new VECTOR2(), sizeof(VECTOR2));
					break;
				}
				case ShaderDataType::Float:
				{
					m_RendererID->CreateVertexCB(m_VUniformVars[i].Name, m_VUniformVars[i].Slot, new float(1.0f), sizeof(float));
					break;
				}
				case ShaderDataType::Int:
				{
					m_RendererID->CreateVertexCB(m_VUniformVars[i].Name, m_VUniformVars[i].Slot, new UINT(1), sizeof(UINT));
					break;
				}
				}
				
			}
		}
		if (m_RendererID->InitPixel(pixelshadersource))
		{
			for (size_t i = 0; i < m_FUniformVars.size(); i++)
			{
				switch (m_FUniformVars[i].Type)
				{
				case ShaderDataType::Mat4:
				{
					m_RendererID->CreatePixelCB(m_FUniformVars[i].Name, m_FUniformVars[i].Slot, new MATRIX4(), sizeof(MATRIX4));
					break;
				}
				case ShaderDataType::Mat3:
				{
					m_RendererID->CreatePixelCB(m_FUniformVars[i].Name, m_FUniformVars[i].Slot, new MATRIX3(), sizeof(MATRIX3));
					break;
				}
				case ShaderDataType::Float4:
				{
					m_RendererID->CreatePixelCB(m_FUniformVars[i].Name, m_FUniformVars[i].Slot, new VECTOR4(), sizeof(VECTOR4));
					break;
				}
				case ShaderDataType::Float3:
				{
					m_RendererID->CreatePixelCB(m_FUniformVars[i].Name, m_FUniformVars[i].Slot, new VECTOR3(), sizeof(VECTOR3));
					break;
				}
				case ShaderDataType::Float2:
				{
					m_RendererID->CreatePixelCB(m_FUniformVars[i].Name, m_FUniformVars[i].Slot, new VECTOR2(), sizeof(VECTOR2));
					break;
				}
				case ShaderDataType::Float:
				{
					m_RendererID->CreatePixelCB(m_FUniformVars[i].Name, m_FUniformVars[i].Slot, new float(1.0f), sizeof(float));
					break;
				}
				case ShaderDataType::Int:
				{
					m_RendererID->CreatePixelCB(m_FUniformVars[i].Name, m_FUniformVars[i].Slot, new UINT(1), sizeof(UINT));
					break;
				}
				}

			}
		}
		//get constant buffers



	}


	










}
