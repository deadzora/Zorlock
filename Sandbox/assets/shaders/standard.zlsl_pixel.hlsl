//version 330 core
#define NUM_LIGHTS 16
struct lightbase
{
	float4 lightpos;   
    float4 lightcolor;
	float radius;
    float strength;
};
struct surfaceproperties
{
	float specular;
	float shininess;
};
cbuffer c_lights_buffer : register(b2)
{
lightbase lights[NUM_LIGHTS];
};
cbuffer c_u_SurfaceProperties_buffer : register(b3)
{
surfaceproperties u_SurfaceProperties;
};
cbuffer c_u_Ambient_buffer : register(b4)
{
float4 u_Ambient;
};
cbuffer c_u_ViewPosition_buffer : register(b5)
{
float4 u_ViewPosition;
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
	float4 appliedlight = u_Ambient;
	float4 viewDir = normalize(u_ViewPosition - input.v_World);
	
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
		float4 lightDir = normalize(lights[i].lightpos - input.v_World); 
		float4 reflectDir = reflect(-lightDir, input.v_Normal); 
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_SurfaceProperties.shininess);
		float4 specular = (u_SurfaceProperties.specular * spec) * lights[i].lightcolor;  
		float diff = max(dot(input.v_Normal, lightDir), 0.0);
		float distancetolight = distance(input.v_World,lights[i].lightpos);
		float attenuationFactor = (1.0f + lights[i].radius) / (1.0f + 0.5f * distancetolight + 0.1f * pow(distancetolight, 2));
		diff *= attenuationFactor;
		float4 diffuse = diff * lights[i].lightcolor;
		float4 result = (u_Ambient + diffuse + specular) * pixelcolor;
		appliedlight += result;
    }
	color = pixelcolor * appliedlight;
	return color;

}

