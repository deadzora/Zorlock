Texture2D u_Texture : TEXTURE : register(t0);
SamplerState u_TextureSampler : SAMPLER : register(s0);
//type 
//version 330 core
struct PS_INPUT
{
	float4 v_Position : SV_POSITION;
	float3 v_Normal : NORMAL;
	float3 v_Color : COLOR;
	float2 v_TexCoord : TEXCOORD;
};
float4 main(PS_INPUT input) : SV_Target
{
	float4 color;


	float4 bcolor = float4(input.v_Color,1.0);
	color = u_Texture.Sample(u_TextureSampler,input.v_TexCoord) ;
	return color;

}

