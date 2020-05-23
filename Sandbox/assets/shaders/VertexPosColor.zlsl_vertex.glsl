//type vertex
#version 330 core
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
out vec4 v_Color;
out vec4 v_Position;

void main()
{
	v_Color = a_Color;
	v_Position = a_Position;
	v_Position = u_Transform*v_Position;	
	v_Position = u_ViewProjection*v_Position;
	gl_Position=v_Position;
}
