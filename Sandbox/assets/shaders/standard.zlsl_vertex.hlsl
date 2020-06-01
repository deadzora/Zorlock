//version 330 core
#define MAX_BONES 100
cbuffer c_u_ViewProjection_buffer : register(b0)
{
float4x4 u_ViewProjection;
};
cbuffer c_u_Transform_buffer : register(b1)
{
float4x4 u_Transform;
};
cbuffer c_u_Bones_buffer : register(b2)
{
float4x4 u_Bones;
};
//type 
struct VS_INPUT
{
	float4 a_Position : POSITION;
	float3 a_Normal : NORMAL;
	float3 a_Color : COLOR;
	float2 a_TexCoord : TEXCOORD;
	float4 a_BoneIDs : BLENDINDICES;
	float4 a_Weights : BLENDWEIGHT;
};
struct PS_INPUT
{
	float4 v_Position : SV_POSITION;
	float4 v_Normal : NORMAL;
	float3 v_Color : COLOR;
	float2 v_TexCoord : TEXCOORD;
	float4 v_World : WORLD_POSITION;
};
PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT) 0; 

	output.v_TexCoord = input.a_TexCoord;
	output.v_Normal = float4(input.a_Normal,1.0);
	output.v_Normal = mul(u_Transform,output.v_Normal);
	output.v_Normal = normalize(output.v_Normal);
	output.v_Color = input.a_Color;
	output.v_Position = input.a_Position;
	output.v_Position = mul(u_ViewProjection,output.v_Position);	
	output.v_World = mul(u_Transform,input.a_Position);	
	return output;

}

