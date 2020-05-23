//type fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;
in float v_TilingFactor;
uniform sampler2D u_Textures;

void main()
{
	//color = v_Color;
	color = texture(u_Textures, v_TexCoord * v_TilingFactor) * v_Color;
	
}
