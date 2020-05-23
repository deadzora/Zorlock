cbuffer c_u_ViewProjection_buffer : register(b0)
{
float4x4 u_ViewProjection;
};
//type 
//version 330 core
struct VS_INPUT
{
	float3 a_Position : POSITION;
	float4 a_Color : COLOR;
	float2 a_TexCoord : TEXCOORD;
	float a_TexIndex : PSIZE;
	float a_TilingFactor : BLENDWEIGHT;
};
struct PS_INPUT
{
	float4 v_Position : SV_POSITION;
	float4 v_Color : COLOR;
	float2 v_TexCoord : TEXCOORD;
	float v_TexIndex : PSIZE;
	float v_TilingFactor : BLENDWEIGHT;
};
PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT) 0; 

	
	output.v_Color = input.a_Color;
	output.v_TexCoord = input.a_TexCoord;
	output.v_TexIndex = input.a_TexIndex;
	output.v_TilingFactor = input.a_TilingFactor;
	output.v_Position = float4(input.a_Position,1.0);
	output.v_Position = mul(u_ViewProjection,output.v_Position);
	return output;

}

