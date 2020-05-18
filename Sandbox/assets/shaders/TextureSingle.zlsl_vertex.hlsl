cbuffer c_u_ViewProjection_buffer : register(b0)
{
float4x4 u_ViewProjection;
};
cbuffer c_u_Transform_buffer : register(b1)
{
float4x4 u_Transform;
};
//type 
//version 330 core
struct VS_INPUT
{
	float3 a_Position : POSITION;
	float2 a_TexCoord : TEXCOORD;
};
struct VS_OUTPUT
{
	float4 v_Position : SV_POSITION;
	float2 v_TexCoord : TEXCOORD;
};
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT) 0; 


	output.v_TexCoord = input.a_TexCoord;
	output.v_Position = mul(u_ViewProjection * u_Transform , float4(input.a_Position, 1.0));	
	return output;

}

