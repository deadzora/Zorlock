//type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
uniform mat4 u_ViewProjection;
uniform mat4 u_ViewMatrix;
uniform mat4 u_Transform;
out vec4 pp;

void main()
{

	pp = u_Transform *a_Position;	
	pp = u_ViewMatrix*pp;
	pp = u_ViewProjection*pp;	
	gl_Position=pp;
}
