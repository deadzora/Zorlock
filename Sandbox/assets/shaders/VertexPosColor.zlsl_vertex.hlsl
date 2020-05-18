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
	float4 a_Color : COLOR;
};
struct VS_OUTPUT
{
	float4 v_Color : COLOR;
	float4 pp : SV_POSITION;
};
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT) 0; 

	output.v_Color = input.a_Color;
	output.pp = mul(u_ViewProjection * u_Transform , float4(input.a_Position, 1.0));
	return output;

}

