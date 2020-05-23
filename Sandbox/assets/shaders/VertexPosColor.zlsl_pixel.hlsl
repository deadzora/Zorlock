//type 
//version 330 core
struct PS_INPUT
{
	float4 v_Color : COLOR;
	float4 v_Position : SV_POSITION;
};
/* Change function body return type to 	float4 color;
*/
float4 main(PS_INPUT input) : SV_Target
{
	float4 color;


	color = float4(input.v_Position.x,input.v_Position.y,input.v_Position.z,1.0) * 0.5 + 0.5;
	return color;

}

