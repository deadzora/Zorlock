#pragma once

namespace Zorlock
{
	template <class A>
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() {
			delete buffer;
		}
		template <class T>
		UniformBuffer(std::string buffername, T* uniformblob, unsigned int index) {
		
			buffer = new A<T>(buffername, uniformblob, index);
		
		};
		
		void Bind(void* shaderdata) 		
		{
			buffer->Bind(shaderdata);
		};
		template <class T>
		void UpdateData(T* uniformblob)
		{
			buffer->UpdateData(uniformblob);
		};
		template <class T>
		void Unbind()
		{
			buffer->Unbind();
		};

	protected:
		A* buffer;
	};

}