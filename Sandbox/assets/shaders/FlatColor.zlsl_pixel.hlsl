cbuffer c_u_Color_buffer : register(b0)
{
float3 u_Color;
};
//type 
//version 330 core
struct VS_INPUT
{
	float4 v_Position : SV_POSITION;
};
/*Change function body return type to 	float4 color;
*/
float main(VS_INPUT input) : SV_Target
{
	float4 color;


	color = float4(u_Color,1.0);
	return color;

}

