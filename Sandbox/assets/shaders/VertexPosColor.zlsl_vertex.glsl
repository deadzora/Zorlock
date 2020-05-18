//type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
out vec4 v_Color;
out vec4 pp;

void main()
{
	v_Color = a_Color;
	pp = u_ViewProjection * u_Transform*vec4(a_Position, 1.0);
	gl_Position=pp;
}
