#include "ZLpch.h"
#include "Zorlock/Renderer/Shader.h"
#include "Zorlock/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/DX11/DX11Shader.h"


namespace Zorlock {

	ShaderLibrary shaderLibrary;
	Ref<ShaderLibrary> m_shaderLibrary;

	void Shader::Process()
	{
		uint32_t vertexuniforms = 0;
		uint32_t vertexsamplers = 0;

		uint32_t pixeluniforms = 0;
		uint32_t pixelsamplers = 0;
		m_VInputVars.clear();
		for (size_t i = 0; i < parser->vlayoutVars.size(); i++)
		{

				ShaderVariable s;
				s.Name = parser->vlayoutVars[i].varname;
				s.SemanticName = parser->s_mapHLSLLayouts[parser->vlayoutVars[i].semantic];
				s.Slot = parser->vlayoutVars[i].index;
				s.Type = ShaderLibrary::GetInstance()->GetMappedValue(parser->vlayoutVars[i].vartype);
				s.Size = ShaderDataTypeSize(s.Type);
				m_VInputVars.push_back(s);

		}
		m_VOutputVars.clear();
		for (size_t i = 0; i < parser->voutVars.size(); i++)
		{
			ShaderVariable s;
			s.Name = parser->voutVars[i].varname;
			s.Slot = parser->voutVars[i].index;
			s.Type = ShaderLibrary::GetInstance()->GetMappedValue(parser->voutVars[i].vartype);
			s.Size = ShaderDataTypeSize(s.Type);
			m_VOutputVars.push_back(s);
		}
		m_VUniformVars.clear();
		for (size_t i = 0; i < parser->vertexUniforms.size(); i++)
		{
			if (parser->vertexUniforms[i].command == ZLSLParser::VarCommandValue::Uniform)
			{
				ShaderVariable s;
				s.Name = parser->vertexUniforms[i].varname;
				s.Slot = i;//parser->vertexUniforms[i].index;
				s.Type = ShaderLibrary::GetInstance()->GetMappedValue(parser->vertexUniforms[i].vartype);
				s.Size = ShaderDataTypeSize(s.Type);
				m_VUniformVars.push_back(s);
				if (parser->vertexUniforms[i].vartype != Zorlock::ZLSLParser::SAMPLER2D)
				{
					vertexuniforms++;
				}
			}
		}
		m_VSamplerVars.clear();
		for (size_t i = 0; i < parser->vertexSamplers.size(); i++)
		{
			if (parser->vertexSamplers[i].command == ZLSLParser::VarCommandValue::Uniform)
			{
				ShaderVariable s;
				s.Name = parser->vertexSamplers[i].varname;
				s.Slot = vertexsamplers;//parser->vertexUniforms[i].index;
				s.Type = ShaderLibrary::GetInstance()->GetMappedValue(parser->vertexSamplers[i].vartype);
				s.Size = ShaderDataTypeSize(s.Type);
				m_VSamplerVars.push_back(s);
				if (parser->vertexSamplers[i].vartype == Zorlock::ZLSLParser::SAMPLER2D)
				{
					vertexsamplers++;
				}
			}
		}
		m_FUniformVars.clear();
		for (size_t i = 0; i < parser->pixelUniforms.size(); i++)
		{
			if (parser->pixelUniforms[i].command == ZLSLParser::VarCommandValue::Uniform)
			{
				ShaderVariable s;
				s.Name = parser->pixelUniforms[i].varname;
				if (parser->vertexUniforms[i].vartype != Zorlock::ZLSLParser::SAMPLER2D)
				{
					s.Slot = (vertexuniforms+ pixeluniforms);
				}
				else {
					s.Slot = i;
				}
				//parser->pixelUniforms[i].index;
				s.Type = ShaderLibrary::GetInstance()->GetMappedValue(parser->pixelUniforms[i].vartype);
				s.Size = ShaderDataTypeSize(s.Type);
				s.isArray = parser->pixelUniforms[i].isArray;
				m_FUniformVars.push_back(s);
				if (parser->vertexUniforms[i].vartype != Zorlock::ZLSLParser::SAMPLER2D)
				{
					pixeluniforms++;
				}
			}
		}
		m_FSamplerVars.clear();
		for (size_t i = 0; i < parser->pixelSamplers.size(); i++)
		{
			if (parser->pixelSamplers[i].command == ZLSLParser::VarCommandValue::Uniform)
			{
				ShaderVariable s;
				s.Name = parser->pixelSamplers[i].varname;
				s.Slot = pixelsamplers;//parser->vertexUniforms[i].index;
				s.Type = ShaderLibrary::GetInstance()->GetMappedValue(parser->pixelSamplers[i].vartype);
				s.Size = ShaderDataTypeSize(s.Type);
				m_FSamplerVars.push_back(s);
				if (parser->pixelSamplers[i].vartype == Zorlock::ZLSLParser::SAMPLER2D)
				{
					pixelsamplers++;
				}
			}
		}
		GenerateLayout();
	}

	void Shader::CreateParser()
	{
		parser = CreateRef<ZLSLParser>();
	}

	void Shader::GenerateLayout()
	{
		ShaderLayout.Clear();
		for (size_t i = 0; i < m_VInputVars.size(); i++)
		{
			ShaderVariable s = GetSlotVariable(i);
			BufferElement a;
			a.Name = s.Name;
			a.SemanticName = s.SemanticName;
			a.Type = s.Type;
			a.Size = s.Size;
			ShaderLayout.Add(a);
		}
		ShaderLayout.CalculateOffsetsAndStride();
	}

	BufferLayout& Shader::GetLayout()
	{
		if (ShaderLayout.Size() == 0)
		{
			Process();
		}
		return ShaderLayout;
	}

	ShaderVariable& Shader::GetSlotVariable(uint32_t index)
	{
		for (size_t i = 0; i < m_VInputVars.size(); i++)
		{
			if (m_VInputVars[i].Slot == index)
			{
				return m_VInputVars[i];
			}
		}
	}



	Ref<Shader> Shader::Create(const std::string& name, const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(name, filepath);
		case RendererAPI::API::DX11:	return CreateRef<DX11Shader>(name, filepath);
		}

		return nullptr;

	}

	Ref<Shader> Shader::CreateFromString(const std::string& value)
	{
		Ref<Shader> shader = nullptr;

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  shader = CreateRef<OpenGLShader>();
		case RendererAPI::API::DX11:  shader = CreateRef<DX11Shader>();
		}
		if (shader != nullptr)
		{
			shader->parser->ParseString(value);
			shader->Process();
			//shader->PostProcess();

		}
		else {
			ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}

		return shader;
	}

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(filepath);
			case RendererAPI::API::DX11:	return CreateRef<DX11Shader>(filepath);
		}

		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
			case RendererAPI::API::DX11:	return CreateRef<DX11Shader>(name, vertexSrc, fragmentSrc);
		}

		return nullptr;
	}

	ShaderLibrary::ShaderLibrary()
	{
		ShaderVarMap[ZLSLParser::VariableTypes::VAR_NONE] = ShaderDataType::None;
		ShaderVarMap[ZLSLParser::VariableTypes::FLOAT] = ShaderDataType::Float;
		ShaderVarMap[ZLSLParser::VariableTypes::INT] = ShaderDataType::Int;
		ShaderVarMap[ZLSLParser::VariableTypes::BOOL] = ShaderDataType::Bool;
		ShaderVarMap[ZLSLParser::VariableTypes::VEC2] = ShaderDataType::Float2;
		ShaderVarMap[ZLSLParser::VariableTypes::VEC3] = ShaderDataType::Float3;
		ShaderVarMap[ZLSLParser::VariableTypes::VEC4] = ShaderDataType::Float4;
		ShaderVarMap[ZLSLParser::VariableTypes::IVEC2] = ShaderDataType::Int2;
		ShaderVarMap[ZLSLParser::VariableTypes::IVEC3] = ShaderDataType::Int3;
		ShaderVarMap[ZLSLParser::VariableTypes::IVEC4] = ShaderDataType::Int4;
		ShaderVarMap[ZLSLParser::VariableTypes::MAT3] = ShaderDataType::Mat3;
		ShaderVarMap[ZLSLParser::VariableTypes::MAT4] = ShaderDataType::Mat4;
		ShaderVarMap[ZLSLParser::VariableTypes::SAMPLER2D] = ShaderDataType::Sampler2D;
		ismapped = true;

		
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		ZL_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(name, filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		ZL_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	Ref<Shader> ShaderLibrary::GetStandard()
	{
		if (m_standardShader == nullptr)
		{
			m_standardShader = Shader::Create("Standard", "assets/shaders/standard.zlsl");
			m_standardShader->Bind();
			m_standardShader->SetInt("u_Texture", 0);
		}
		return m_standardShader;
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

	ShaderDataType ShaderLibrary::GetMappedValue(ZLSLParser::VariableTypes v)
	{
		return ShaderVarMap[v];
	}

	Ref<ShaderLibrary> ShaderLibrary::GetInstance()
	{
		if (shaderLibrary.ismapped == false)
		{
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::VAR_NONE] = ShaderDataType::None;
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::FLOAT] = ShaderDataType::Float;
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::INT] = ShaderDataType::Int;
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::BOOL] = ShaderDataType::Bool;
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::VEC2] = ShaderDataType::Float2;
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::VEC3] = ShaderDataType::Float3;
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::VEC4] = ShaderDataType::Float4;
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::IVEC2] = ShaderDataType::Int2;
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::IVEC3] = ShaderDataType::Int3;
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::IVEC4] = ShaderDataType::Int4;
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::MAT3] = ShaderDataType::Mat3;
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::MAT4] = ShaderDataType::Mat4;
			shaderLibrary.ShaderVarMap[ZLSLParser::VariableTypes::SAMPLER2D] = ShaderDataType::Sampler2D;
			shaderLibrary.ismapped = true;
		}
		if (m_shaderLibrary == nullptr)
		{
			m_shaderLibrary = CreateRef <ShaderLibrary>(shaderLibrary);
		}
		return m_shaderLibrary;
	}

}