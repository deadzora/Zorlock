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
	float4 a_BoneIDs : BINORMAL;
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

	output.v_Color = input.a_Color;
	output.v_Position = input.a_Position;
	row_major float4x4 wpos = u_Transform;
	bool hasweight = false;	
	if(input.a_Weights.x > 0.0)
	{
		row_major float4x4 BoneTransform = u_Bones[int(input.a_BoneIDs.x)];
		wpos += mul(input.a_Weights.x,BoneTransform);
		hasweight = true;
	}	
	if(input.a_Weights.y > 0.0)
	{
		row_major float4x4 BoneTransform = u_Bones[int(input.a_BoneIDs.y)];
		wpos += mul(input.a_Weights.y,BoneTransform);
		hasweight = true;
	}
	if(input.a_Weights.z > 0.0)
	{
		row_major float4x4 BoneTransform = u_Bones[int(input.a_BoneIDs.z)];
		wpos += mul(input.a_Weights.z,BoneTransform);
		hasweight = true;
	}
	if(input.a_Weights.w > 0.0)
	{
		row_major float4x4 BoneTransform = u_Bones[int(input.a_BoneIDs.w)];
		wpos += mul(input.a_Weights.w,BoneTransform);
		hasweight = true;
	}	
	if(hasweight==true)
	{
		float finalWeight = 1.0 - ( input.a_Weights.x + input.a_Weights.y + input.a_Weights.z + input.a_Weights.w );
		wpos += (u_Transform * finalWeight);
		hasweight = true;
	}
	
	output.v_Position = mul(wpos,output.v_Position);	
	output.v_Normal = mul(wpos,output.v_Normal);
	output.v_Normal = normalize(output.v_Normal);
	output.v_World = mul(wpos,input.a_Position);
	output.v_Position = mul(u_ViewProjection,output.v_Position);				
	return output;

}

