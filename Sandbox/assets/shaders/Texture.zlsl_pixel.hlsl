Texture2DArray u_Textures : TEXTURE : register(t0);
SamplerState u_TexturesSampler : SAMPLER : register(s0);
//type 
//version 330 core
struct VS_INPUT
{
	float4 v_Position : SV_POSITION;
	float4 v_Color : COLOR;
	float2 v_TexCoord : TEXCOORD;
	float v_TexIndex : PSIZE;
	float v_TilingFactor : PSIZE;
};
/* Change function body return type to 	float4 color;
*/
float main(VS_INPUT input) : SV_Target
{
	float4 color;


	color = u_Textures.Sample(u_TexturesSampler, float3(input.v_TexCoord * input.v_TilingFactor,int(input.v_TexIndex))) * input.v_Color;
	return color;

}

