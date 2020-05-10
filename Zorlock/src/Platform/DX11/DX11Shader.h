#pragma once

#include "Zorlock/Renderer/Shader.h"
#include <d3d11.h>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace DX11Raz {
	class RazShader;
}

namespace Zorlock {

	class DX11Shader : public Shader
	{
	public:
		DX11Shader();
		DX11Shader(const std::string& filepath);
		DX11Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~DX11Shader();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Apply() const override;
		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }
		/*
		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		*/
		/* Each offset is measured in shader constants, which are 16 bytes (4*32-bit components). 
		Therefore, an offset of 16 indicates that the start of the associated constant buffer is 
		256 bytes into the constant buffer. Each offset must be a multiple of 16 constants.*/

		template <class T>
		UINT CreateVertexBufferData(T* bufferblob)
		{
			
			return m_RendererID->CreateVertexCB(static_cast<void*>(bufferblob), sizeof(T));
		};

		template <class T>
		UINT CreatePixelBufferData(T* bufferblob)
		{
			return m_RendererID->CreatePixelCB(static_cast<void*>(bufferblob), sizeof(T));
		};

		template <class T>
		void UpdateVertexBufferData(T* bufferblob,UINT index)
		{
			m_RendererID->UpdateVertexCB(static_cast<void*>(bufferblob), sizeof(T), UINT index);
		};

		template <class T>
		void UpdatePixelBufferData(T* bufferblob, UINT index)
		{
			pbufferSize = sizeof(T);
			m_RendererID->UpdatePixelCB(static_cast<void*>(bufferblob), sizeof(T), UINT index);
		};

		template <class T>
		T* SetVertexBufferData(UINT index)
		{
			return static_cast<T*>(m_RendererID->GetVertexCBData(index));
		};

		template <class T>
		T* SetPixelBufferData(UINT index)
		{
			return static_cast<T*>(m_RendererID->GetPixelCBData(index));
		};

		template <class T>
		void UploadVertexBufferData(T* bufferblob, UINT index)
		{
			m_RendererID->ApplyVertexCB(static_cast<void*>(bufferblob),sizeof(T),index);
		};

		template <class T>
		void UploadPixelBufferData(T* bufferblob, UINT index)
		{
			m_RendererID->ApplyPixelCB(static_cast<void*>(bufferblob),sizeof(T),index);
		};

		

	private:

		DX11Raz::RazShader * m_RendererID;
		std::string m_Name;
	};

}