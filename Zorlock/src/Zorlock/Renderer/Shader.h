#pragma once

#include <string>
#include <unordered_map>
#include "Zorlock/Core/Math.h"
//Need to Phase out GLM from base classes
#include <glm/glm.hpp>

namespace Zorlock {


	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		ZL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct ShaderVariable {
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Slot;
		size_t Offset;
		bool Normalized;

		ShaderVariable() : Name(""), Type(ShaderDataType::None), Size(0), Offset(0), Normalized(false), Slot(0)
		{};

		ShaderVariable(ShaderDataType type, const std::string & name, bool normalized)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized), Slot(0)
		{
		}

		ShaderVariable(ShaderDataType type, const std::string& name, uint32_t slot , size_t offset, bool normalized)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(offset), Normalized(normalized), Slot(slot)
		{
		}
		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3; // 3* float3
			case ShaderDataType::Mat4:    return 4; // 4* float4
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			ZL_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}

	};


	class ShaderVariables
	{
	public:
		ShaderVariables() {};
		ShaderVariables(const std::initializer_list<ShaderVariable>& variables)
			: m_Variables(variables)
		{
			CalculateOffsetsAndStride();
		}
		const std::vector<ShaderVariable>& GetElements() const { return m_Variables; }
		std::vector<ShaderVariable>::iterator begin() { return m_Variables.begin(); }
		std::vector<ShaderVariable>::iterator end() { return m_Variables.end(); }
		std::vector<ShaderVariable>::const_iterator begin() const { return m_Variables.begin(); }
		std::vector<ShaderVariable>::const_iterator end() const { return m_Variables.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Variables)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		uint32_t m_Stride = 0;
		std::vector<ShaderVariable> m_Variables;

	};

	class ZLSLParser;

	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const {};
		virtual void Unbind() const {};
		//compatibility function for us poor folk who have to use uniform buffers.
		virtual void Apply() const {};
		virtual void SetInt(const std::string& name, int value) {};
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) {};
		virtual void SetFloat(const std::string& name, float value) {};
		ZL_DEPRECATED("No longer using glm in base classes")
			virtual void SetFloat3(const std::string& name, const glm::vec3& value) {}; //making them non abstract so there's no need to override
		virtual void SetFloat3(const std::string& name, const VECTOR3& value) {};
		ZL_DEPRECATED("No longer using glm in base classes")
			virtual void SetFloat4(const std::string& name, const glm::vec4& value) {}; //making them non abstract so there's no need to override
		virtual void SetFloat4(const std::string& name, const VECTOR4& value) {};
		ZL_DEPRECATED("No longer using glm in base classes")
			virtual void SetMat4(const std::string& name, const glm::mat4& value) {}; //making them non abstract so there's no need to override
		virtual void SetMat4(const std::string& name, const MATRIX4& value) {};
		virtual void PostProcess() {};
		virtual const std::string& GetName() const { return "";  };
		bool Preprocess();
		void CreateParser();
		static Ref<Shader> CreateFromFile(const std::string& filepath);
		static Ref<Shader> CreateFromString(const std::string& value);

		ZL_DEPRECATED("Using Material to Initialize Shader")
		static Ref<Shader> Create(const std::string& filepath);
		ZL_DEPRECATED("Using Material to Initialize Shader")
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	protected:
		Ref<ZLSLParser> parser;
		std::shared_ptr<ShaderVariables> m_VInputVars;
		std::shared_ptr<ShaderVariables> m_VOutputVars;
		std::shared_ptr<ShaderVariables> m_VUniformVars;
		std::shared_ptr<ShaderVariables> m_FUniformVars;
	};


	

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		Ref<Shader> Get(const std::string& name);
		static ShaderLibrary* Instance();
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}