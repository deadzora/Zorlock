cbuffer c_u_Color_buffer : register(b2)
{
float3 u_Color;
};
//type 
//version 330 core
struct PS_INPUT
{
	float4 v_Position : SV_POSITION;
};
float4 main(PS_INPUT input) : SV_Target
{
	float4 color;


	color = float4(u_Color,1.0);
	return color;

}

