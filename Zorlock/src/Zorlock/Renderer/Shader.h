#pragma once
#include <string>
#include <unordered_map>

#include "Zorlock/Core/Math.h"
//Need to Phase out GLM from base classes
#include <glm/glm.hpp>
#include "ZLSLParser.h"

namespace Zorlock {


	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool, Sampler2D
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

		//ZL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	struct BufferElement
	{
		std::string Name;
		std::string SemanticName;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
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


	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		void Add(BufferElement& element) { m_Elements.push_back(element); };
		void Clear() { m_Elements.clear(); };
		size_t Size() { return m_Elements.size(); };
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	public:
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};





	struct ShaderVariable {
		std::string Name;
		std::string SemanticName;
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


	};

	/*
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
	*/



	class Shader
	{
	public:

		virtual ~Shader() {
		};

		virtual void Bind() const {};
		virtual void Unbind() const {};
		//compatibility function for us poor folk who have to use uniform buffers.
		virtual void Apply() const {};
		virtual void SetInt(const std::string& name, int value) {};
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) {};
		virtual void SetFloat(const std::string& name, float value) {};
		
		//ZL_DEPRECATED("No longer using glm in base classes")
		//virtual void SetFloat3(const std::string& name, const glm::vec3& value) {}; //making them non abstract so there's no need to override
		
		virtual void SetFloat3(const std::string& name, const VECTOR3& value) {};
		
		//ZL_DEPRECATED("No longer using glm in base classes")
		//virtual void SetFloat4(const std::string& name, const glm::vec4& value) {}; //making them non abstract so there's no need to override
		
		virtual void SetFloat4(const std::string& name, const VECTOR4& value) {};
		
		//ZL_DEPRECATED("No longer using glm in base classes")
		virtual void SetMat4(const std::string& name, const glm::mat4& value) {}; //making them non abstract so there's no need to override
		
		virtual void SetMat4(const std::string& name, const MATRIX4& value) {};
		
		virtual void SetTextureArray(const std::string& name, void* values, uint32_t count) {};

		virtual void PostProcess() {};
		//Helper function across graphics API
		virtual void* GetShaderID() const =0;


		void Process();
		virtual const std::string& GetName() const { return "";  };
		void CreateParser();
		void GenerateLayout();
		BufferLayout& GetLayout();
		ShaderVariable& GetSlotVariable(uint32_t index);
		static Ref<Shader> CreateFromString(const std::string& value);

		ZL_DEPRECATED("Using Material to Initialize Shader")
		static Ref<Shader> Create(const std::string& filepath);

		ZL_DEPRECATED("Using Material to Initialize Shader")
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);


		static Ref<Shader> Create(const std::string& name, const std::string& filepath);
	protected:
		Ref<ZLSLParser> parser;
		std::vector<ShaderVariable> m_VInputVars;
		std::vector<ShaderVariable> m_VOutputVars;
		std::vector<ShaderVariable> m_VUniformVars;
		std::vector<ShaderVariable> m_FUniformVars;
		BufferLayout ShaderLayout;
	};


	

	class ShaderLibrary
	{
	public:
		ShaderLibrary();
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		Ref<Shader> Get(const std::string& name);
		static ShaderLibrary* GetInstance();
		bool Exists(const std::string& name) const;
		ShaderDataType GetMappedValue(ZLSLParser::VariableTypes v);
	private:
		bool ismapped;
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
		std::map<ZLSLParser::VariableTypes, ShaderDataType> ShaderVarMap;
	};

}