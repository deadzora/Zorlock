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
	float4 a_Position : POSITION;
};
struct VS_OUTPUT
{
	float4 v_Position : SV_POSITION;
};
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT) 0; 

	output.v_Position = mul(u_ViewProjection * u_Transform , input.a_Position);
	return output;

}

