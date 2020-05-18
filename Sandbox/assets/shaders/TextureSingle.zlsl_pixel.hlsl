Texture2D u_Texture : TEXTURE : register(t0);
SamplerState u_TextureSampler : SAMPLER : register(s0);
//type 
//version 330 core
struct VS_INPUT
{
	float4 v_Position : SV_POSITION;
	float2 v_TexCoord : TEXCOORD;
};
/*Change function body return type to 	float4 color;
*/
float main(VS_INPUT input) : SV_Target
{
	float4 color;


	color = texture(u_Texture, input.v_TexCoord);
	return color;

}

