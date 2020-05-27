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
	float3 a_Normal : NORMAL;
	float3 a_Color : COLOR;
	float2 a_TexCoord : TEXCOORD;
};
struct PS_INPUT
{
	float4 v_Position : SV_POSITION;
	float3 v_Normal : NORMAL;
	float3 v_Color : COLOR;
	float2 v_TexCoord : TEXCOORD;
};
PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT) 0; 


	output.v_TexCoord = input.a_TexCoord;
	output.v_Normal = input.a_Normal;
	output.v_Color = input.a_Color;
	output.v_Position = input.a_Position;
	output.v_Position = mul(u_Transform,output.v_Position);	
	output.v_Position = mul(u_ViewProjection,output.v_Position);
	output.v_Position = float4(input.a_Position.x,input.a_Position.y,input.a_Position.z,0.0);
	return output;

}

