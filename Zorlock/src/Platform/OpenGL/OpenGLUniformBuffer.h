#pragma once
#include <glm/glm.hpp>


namespace Zorlock
{

	template <class T>
	class OpenGLUniformBuffer
	{
	public:
		virtual ~OpenGLUniformBuffer() {}

		OpenGLUniformBuffer(std::string buffername, T* uniformblob, unsigned int index)
		{
			b_name = buffername;
			b_index = index;
			m_SceneData = uniformblob;
			//Create the buffer
			GLuint uboHandle;
			glGenBuffers(1, &uboHandle);
			m_buffer = static_cast<void*>(*uboHandle);
			glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(T), m_SceneData, GL_DYNAMIC_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, b_index, uboHandle);

		};
		void Bind(void* shaderdata)
		{
			uint32_t p = static_cast<uint32_t>(shaderdata);
			binding = static_cast<void*>(*p);
			GLuint blockIndex = glGetUniformBlockIndex(program, b_name);
			glUniformBlockBinding(program, blockIndex, b_index);
		};

		void UpdateData(T* uniformblob)
		{
			GLuint uboHandle = static_cast<GLuint>(&m_buffer);
			glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(T), m_SceneData, GL_DYNAMIC_DRAW);
		};


		void Unbind() {};
	private:

		std::string b_name;
		unsigned int b_index;
		T* m_SceneData;
	};
};