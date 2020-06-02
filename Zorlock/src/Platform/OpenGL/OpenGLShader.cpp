#include "ZLpch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <ZLSLParser.h>
namespace Zorlock {

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		if (type == "compute")
			return GL_COMPUTE_SHADER;
		ZL_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader() : Shader(), m_RendererID(0)
	{
		
		ZL_PROFILE_FUNCTION();
	}

	OpenGLShader::OpenGLShader(const std::string& filepath) : Shader(), m_RendererID(0)
	{
		ZL_PROFILE_FUNCTION();

		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		// Extract name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : Shader(), m_RendererID(0)
		, m_Name(name)
	{
		ZL_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& filepath) : m_RendererID(0)
	{
		CreateParser();
		parser->Parse(filepath);
		Process();
		printf("COMPILE SHADERS!! \n");
		std::string vertexSrc = parser->GetShader(Zorlock::ZLSLParser::OutPutShaderType::GLSL, Zorlock::ZLSLParser::ShaderSection::VERTEXSHADER);
		std::string fragmentSrc = parser->GetShader(Zorlock::ZLSLParser::OutPutShaderType::GLSL, Zorlock::ZLSLParser::ShaderSection::FRAGMENTSHADER);
		parser->SaveShader(vertexSrc, filepath + "_vertex.glsl");
		parser->SaveShader(fragmentSrc, filepath + "_pixel.glsl");

		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(shaderSources);

	}

	OpenGLShader::OpenGLShader(const std::string& source, bool diff) : m_RendererID(0)
	{
	}

	OpenGLShader::~OpenGLShader()
	{
		ZL_PROFILE_FUNCTION();
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		ZL_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else
			{
				ZL_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			ZL_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		ZL_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
			ZL_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
			std::string type = source.substr(begin, eol - begin);
			ZL_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			ZL_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		ZL_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		ZL_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				ZL_CORE_ERROR("{0}", infoLog.data());
				ZL_CORE_ASSERT(false, "Shader compilation failure!");
				printf("Shader Compile Failure \n");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}
		
		m_RendererID = program;

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			
			for (auto id : glShaderIDs)
				glDeleteShader(id);

			ZL_CORE_ERROR("{0}", infoLog.data());
			ZL_CORE_ASSERT(false, "Shader link failure!");
			
			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}
	}

	void OpenGLShader::Bind() const
	{
		ZL_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		ZL_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::Apply() const
	{
		//Can send Uniform buffers here.
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		ZL_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetTextureArray(const std::string& name, void* values, uint32_t count)
	{
		UploadUniformDataArray(name, values, count);
		
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		ZL_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}
	/*
	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		ZL_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}
	*/
	void OpenGLShader::SetFloat3(const std::string& name, const VECTOR3& value)
	{
		ZL_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}
	/*
	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		ZL_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}
	*/
	void OpenGLShader::SetFloat4(const std::string& name, const VECTOR4& value)
	{
		ZL_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}
	/*
	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		ZL_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}
	*/
	void OpenGLShader::SetMat4(const std::string& name, const MATRIX4& value)
	{
		ZL_PROFILE_FUNCTION();
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::SetBuffer(const std::string& name, const void* buffer, uint32_t size, uint32_t count)
	{
		UploadUniformBuffer(name, buffer, size, count);
		ZL_PROFILE_FUNCTION();

	}

	void* OpenGLShader::GetShaderID() const
	{
		return (void*)&m_RendererID;
	}




	void OpenGLShader::PostProcess()
	{
		
		/*
		std::string vertexSrc = parser->GetShader(Zorlock::ZLSLParser::OutPutShaderType::GLSL, Zorlock::ZLSLParser::ShaderSection::VERTEXSHADER);
		std::string fragmentSrc = parser->GetShader(Zorlock::ZLSLParser::OutPutShaderType::GLSL, Zorlock::ZLSLParser::ShaderSection::FRAGMENTSHADER);
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(shaderSources);
		*/
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformDataArray(const std::string& name, void* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		int * vals = static_cast<int*>(values);
		glUniform1iv(location, count, vals);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}
	/*
	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}
	*/
	void OpenGLShader::UploadUniformFloat2(const std::string& name, const VECTOR2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const VECTOR3& value)
	{

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}
	/*
	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	*/
	void OpenGLShader::UploadUniformFloat4(const std::string& name, const VECTOR4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	/*
	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	*/
	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_TRUE, glm::value_ptr(matrix));
	}
	


	void OpenGLShader::UploadUniformMat3(const std::string& name, const MATRIX3& matrix)
	{
		MATRIX3 m = matrix;

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_TRUE, m.To3x3PtrArray());
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const MATRIX4& matrix)
	{
		MATRIX4 m = matrix;

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_TRUE, m.To4x4PtrArray());
	}

	void OpenGLShader::UploadUniformBuffer(const std::string& name, const void* buffer, uint32_t size, uint32_t count)
	{
		//get the index location and size of the block
		GLuint block_index = glGetUniformBlockIndex(m_RendererID, name.c_str());
		GLint block_size = size * count;
		glGetActiveUniformBlockiv(m_RendererID, block_index, GL_UNIFORM_BLOCK_DATA_SIZE, &block_size);

		//create temporary buffer on CPU side to hold the data
		GLubyte* block_buffer = (GLubyte*)malloc(size*count);
		//fill temporary buffer
		memcpy(block_buffer, buffer, size * count);
		//create OpenGL buffer and bind it to the uniform block
		GLuint buffer_handle;
		glGenBuffers(1, &buffer_handle);
		glBindBuffer(GL_UNIFORM_BUFFER, buffer_handle);
		glBufferData(GL_UNIFORM_BUFFER, block_size, block_buffer, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, block_index, buffer_handle);
	}



}