#version 330 core
//type vertex
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Color;
layout(location = 3) in vec2 a_TexCoord;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
out vec4 v_Position;
out vec4 v_Normal;
out vec3 v_Color;
out vec2 v_TexCoord;
out vec4 v_World;

void main()
{

	v_TexCoord = a_TexCoord;
	v_Normal = vec4(a_Normal,1.0);
	vec4 worldN = u_Transform*v_Normal;
	v_Normal = normalize(worldN);
	v_Color = a_Color;
	v_Position = a_Position;
	v_Position = u_ViewProjection*v_Position;	
	v_World = u_Transform*v_Position;	
	gl_Position=v_Position;
}

