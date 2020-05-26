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
struct PS_INPUT
{
	float4 v_Position : SV_POSITION;
};
PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT) 0; 

	output.v_Position = input.a_Position;
	output.v_Position = mul(u_Transform,output.v_Position);	
	output.v_Position = mul(u_ViewProjection,output.v_Position);
	return output;

}

