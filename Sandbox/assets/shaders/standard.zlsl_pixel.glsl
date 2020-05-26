//type fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec4 Z_Position;
in vec3 v_Normal;
in vec3 v_Color;
in vec2 v_TexCoord;
uniform sampler2D u_Texture;

void main()
{
	vec4 bcolor = vec4(v_Color,1.0);
	color = texture(u_Texture, v_TexCoord);
	
}
