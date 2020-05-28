//version 330 core
Texture2D u_Textures : TEXTURE : register(t0);
SamplerState u_TexturesSampler : SAMPLER : register(s0);
//type 
struct PS_INPUT
{
	float4 v_Position : SV_POSITION;
	float4 v_Color : COLOR;
	float2 v_TexCoord : TEXCOORD;
	float v_TexIndex : PSIZE;
	float v_TilingFactor : BLENDWEIGHT;
};
float4 main(PS_INPUT input) : SV_Target
{
	float4 color;

	//color = input.v_Color;
	color = u_Textures.Sample(u_TexturesSampler,input.v_TexCoord * input.v_TilingFactor) * input.v_Color;
	return color;

}

