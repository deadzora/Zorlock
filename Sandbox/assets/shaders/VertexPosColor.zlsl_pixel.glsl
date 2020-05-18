//type fragment
#version 330 core
layout(location = 0) out vec3 color;
in vec4 pp;
in vec4 v_Color;

void main()
{
	color = vec3(pp.x,pp.y,pp.z) * 0.5 + 0.5;
	
}
