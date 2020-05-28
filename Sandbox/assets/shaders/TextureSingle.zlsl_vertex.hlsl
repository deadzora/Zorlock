cbuffer c_u_Transform_buffer : register(b0)
{
float4x4 u_Transform;
};
//type 
//version 330 core
struct VS_INPUT
{
	float4 a_Position : POSITION;
	float2 a_TexCoord : TEXCOORD;
};
struct PS_INPUT
{
	float4 v_Position : SV_POSITION;
	float2 v_TexCoord : TEXCOORD;
};
PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT) 0; 


	output.v_TexCoord = input.a_TexCoord;
	output.v_Position = input.a_Position;
	output.v_Position = mul(u_Transform,output.v_Position);	
	//output.v_Position = Z_Mul(u_ViewProjection, output.v_Position);
	return output;

}

