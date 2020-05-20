//type 
//version 330 core
struct VS_INPUT
{
	float4 v_Color : COLOR;
	float4 pp : SV_POSITION;
};
/* Change function body return type to 	float3 color;
*/
float main(VS_INPUT input) : SV_Target
{
	float3 color;


	color = float3(input.pp.x,input.pp.y,input.pp.z) * 0.5 + 0.5;
	return color;

}

