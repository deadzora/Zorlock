#pragma once
#include "VertexArray.h"

namespace Zorlock {
	
	class Mesh
	{
	public:
		Mesh();
		~Mesh();
		
	protected:
		Ref<VertexArray> m_VertexArray;
	};
	
	
}