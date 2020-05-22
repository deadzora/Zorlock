//type vertex
#version 330 core
layout(location = 0) in vec4 a_Position;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
out vec4 v_Position;

void main()
{
	v_Position = u_ViewProjection * u_Transform *a_Position;
	gl_Position=v_Position;
}
