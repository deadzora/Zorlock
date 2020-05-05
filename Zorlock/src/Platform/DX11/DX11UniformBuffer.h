#pragma once
#include "Zorlock/Renderer/UniformBuffer.h"

namespace Zorlock
{
	
	
	template <class T>
	class DX11UniformBuffer
	{
	public:
		virtual ~DX11UniformBuffer() {}
		DX11UniformBuffer(std::string buffername, T* uniformblob, unsigned int index)
		{

		};
		void Bind(void* shaderdata) { };
		void UpdateData(T* uniformblob) { };
		void Unbind()  override { };
	private:
		UINT m_RendererID;
		T* m_SceneData;


	};
	
	
}