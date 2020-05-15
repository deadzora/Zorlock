Texture2DArray u_Textures : TEXTURE : register(t0);
SamplerState u_TexturesSampler : SAMPLER : register(s0);
//type 
//version 330 core
struct VS_INPUT
{
	float4 v_Position : SV_POSITION;
	float4 v_Color : COLOR;
	float2 v_TexCoord : TEXCOORD;
	float v_TexIndex;
	float v_TilingFactor;
};
/*Change function body return type to 	float4 color;
*/
float main(VS_INPUT input) : SV_Target
{
	float4 color;


	color = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TilingFactor) * v_Color;
	return color;

}

