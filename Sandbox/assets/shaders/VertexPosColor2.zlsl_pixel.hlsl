//type 
//version 330 core
struct PS_INPUT
{
	float4 pp : SV_POSITION;
};
/* Change function body return type to 	float4 color;
*/
float4 main(PS_INPUT input) : SV_Target
{
	float4 color;


	color = float4(input.pp.x,input.pp.y,input.pp.z,1.0) * 0.5 + 0.5;
	return color;

}

