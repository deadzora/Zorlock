//version 330 core
#pragma pack_matrix( row_major )
#define MAX_BONES 200
cbuffer c_u_ViewProjection_buffer : register(b0)
{
row_major float4x4 u_ViewProjection;
};
cbuffer c_u_Transform_buffer : register(b1)
{
row_major float4x4 u_Transform;
};
cbuffer c_u_Bones_buffer : register(b2)
{
row_major float4x4 u_Bones[MAX_BONES];
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
	
	row_major float4x4 wpos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	row_major float4x4 BoneTransform = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	bool hasweight = false;
	if(input.a_Weights.x > 0.0)
	{
		BoneTransform = u_Bones[int(input.a_BoneIDs.x)];
		wpos += BoneTransform * input.a_Weights.x;
		hasweight = true;
	}	
	if(input.a_Weights.y > 0.0)
	{
		BoneTransform = u_Bones[int(input.a_BoneIDs.y)];
		wpos += BoneTransform * input.a_Weights.y;
		hasweight = true;
	}
	if(input.a_Weights.z > 0.0)
	{
		BoneTransform = u_Bones[int(input.a_BoneIDs.z)];
		wpos += BoneTransform * input.a_Weights.z;
		hasweight = true;
	}
	if(input.a_Weights.w > 0.0)
	{
		float finalWeight = 1.0f - ( input.a_Weights.x + input.a_Weights.y + input.a_Weights.z );
		BoneTransform = u_Bones[int(input.a_BoneIDs.w)];
		wpos += BoneTransform * finalWeight;
		hasweight = true;
	}
	
	if(hasweight==true)
	{	
		output.v_Position = mul(wpos,output.v_Position);	
	} else {	
		output.v_Position = mul(u_Transform,output.v_Position);
	}	
	output.v_Position = mul(u_ViewProjection,output.v_Position);		
	output.v_World = mul(u_Transform,input.a_Position);	
	return output;

}

