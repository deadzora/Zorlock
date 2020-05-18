//type fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec4 v_Position;
uniform vec3 u_Color;

void main()
{
	color = vec4(u_Color,1.0);
	
}
