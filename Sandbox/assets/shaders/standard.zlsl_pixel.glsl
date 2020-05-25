//type fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec4 v_Position;
in vec2 v_TexCoord;
uniform sampler2D u_Texture;

void main()
{
	color = vec4(1,1,1,1);
	//color = texture(u_Texture, v_TexCoord);
	
}
