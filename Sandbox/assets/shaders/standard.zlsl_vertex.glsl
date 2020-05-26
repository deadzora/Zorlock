//type vertex
#version 330 core
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Color;
layout(location = 3) in vec2 a_TexCoord;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
out vec4 v_Position;
out vec3 v_Normal;
out vec3 v_Color;
out vec2 v_TexCoord;

void main()
{

	v_TexCoord = a_TexCoord;
	v_Normal = a_Normal;
	v_Color = a_Color;
	v_Position = a_Position;
	v_Position = u_Transform*v_Position;	
	v_Position = u_ViewProjection*v_Position;
	gl_Position=v_Position;
}
