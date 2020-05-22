//type fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec4 pp;

void main()
{
	color = vec4(pp.x,pp.y,pp.z,1.0) * 0.5 + 0.5;
	
}
