//type 
//version 330 core
struct PS_INPUT
{
	float4 v_Position : SV_POSITION;
	float4 v_Color : COLOR;
};
float4 main(PS_INPUT input) : SV_Target
{
	float4 color;


	color = float4(input.v_Color.x,input.v_Color.y,input.v_Color.z,1.0) * 0.5 + 0.5;
	return color;

}

