//version 330 core
#define NUM_LIGHTS 16
struct lightbase
{
	float4 lightpos;   
    float4 lightcolor;
	float radius;
    float strength;
};
cbuffer c_lights_buffer : register(b2)
{
lightbase lights[NUM_LIGHTS];
};
cbuffer c_u_Ambient_buffer : register(b3)
{
float4 u_Ambient;
};
Texture2D u_Texture : TEXTURE : register(t0);
SamplerState u_TextureSampler : SAMPLER : register(s0);
//type 
struct PS_INPUT
{
	float4 v_Position : SV_POSITION;
	float4 v_Normal : NORMAL;
	float3 v_Color : COLOR;
	float2 v_TexCoord : TEXCOORD;
	float4 v_World : WORLD_POSITION;
};
float4 main(PS_INPUT input) : SV_Target
{
	float4 color;

	float4 pixelcolor = u_Texture.Sample(u_TextureSampler,input.v_TexCoord) ;
	float4 appliedlight = float4(0,0,0,1);
	appliedlight += u_Ambient;
	
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		float4 vectortolight = normalize(lights[i].lightpos - input.v_World);		
		float diffuseintensity = max(dot(vectortolight, input.v_Normal), 0);
		float distancetolight = distance(lights[i].lightpos, input.v_World);
		float attenuationFactor = (1.0f + lights[i].radius) / (1.0f + 0.5f * distancetolight + 0.1f * pow(distancetolight, 2));
		diffuseintensity *= attenuationFactor;
		float4 diffuselight = diffuseintensity * lights[i].strength * lights[i].lightcolor;
		appliedlight += diffuselight;
	}
	color = pixelcolor * appliedlight;
	return color;

}

