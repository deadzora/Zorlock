#include "Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}


ID3D10Blob * Shader::GetBuffer()
{
	return this->m_buffer;
}