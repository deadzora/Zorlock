#include "ZLpch.h"
#include "Zorlock/Renderer/Shader.h"
#include "Zorlock/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/DX11/DX11Shader.h"
#include <ZLSLParser.h>

namespace Zorlock {

	ShaderLibrary shaderLibrary;

	bool Shader::Preprocess()
	{

		return false;
	}

	void Shader::CreateParser()
	{
		parser = CreateRef<ZLSLParser>();
	}

	Ref<Shader> Shader::CreateFromFile(const std::string& filepath)
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
			shader->parser->Parse(filepath);
			shader->PostProcess();
		}
		else {
			ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}

		return shader;
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
			shader->PostProcess();

		}
		else {
			ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}

		return shader;
	}

	Ref<Shader> Shader::Create(const std::string& filepath)
	{

		Ref<Shader> shader = nullptr;
		
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  shader = CreateRef<OpenGLShader>(filepath);
			case RendererAPI::API::DX11:  shader = CreateRef<DX11Shader>(filepath);
		}
		if (shader != nullptr)
		{

		}
		else {
			ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		
		return shader;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		Ref<Shader> shader = nullptr;

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  shader = CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
			case RendererAPI::API::DX11:  shader = CreateRef<DX11Shader>(name, vertexSrc, fragmentSrc);
		}

		if (shader != nullptr)
		{

		}
		else {
			ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}

		return shader;
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
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		ZL_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

	ShaderLibrary* ShaderLibrary::Instance()
	{
		return &shaderLibrary;
	}

}