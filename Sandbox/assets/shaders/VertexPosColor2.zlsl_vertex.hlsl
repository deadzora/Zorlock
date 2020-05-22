cbuffer c_u_ViewProjection_buffer : register(b0)
{
float4x4 u_ViewProjection;
};
cbuffer c_u_ViewMatrix_buffer : register(b1)
{
float4x4 u_ViewMatrix;
};
cbuffer c_u_Transform_buffer : register(b2)
{
float4x4 u_Transform;
};
//type 
//version 330 core
struct VS_INPUT
{
	float3 a_Position : POSITION;
};
struct PS_INPUT
{
	float4 pp : SV_POSITION;
};
PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT) 0; 


	output.pp = mul(u_Transform ,input.a_Position);	
	output.pp = mul(u_ViewMatrix,output.pp);
	output.pp = mul(u_ViewProjection,output.pp);	
	return output;

}

