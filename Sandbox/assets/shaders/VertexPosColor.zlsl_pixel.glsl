//type fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec4 v_Position;
in vec4 v_Color;

void main()
{
	color = vec4(v_Color.x,v_Color.y,v_Color.z,1.0) * 0.5 + 0.5;
	
}
