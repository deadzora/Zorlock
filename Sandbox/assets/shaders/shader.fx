#define NUM_LIGHTS 16

cbuffer cvertbuffer : register(b0)
{
	float4x4 wvpMatrix;
    float4x4 worldMatrix;
};
cbuffer cpixbuffer : register(b1)
{
	float alpha;

};
cbuffer clitbuffer : register(b2)
{
    float lightstrength;
    float3 lightcolor;
    //float dynamiclightattenuation_a[NUM_LIGHTS];
    //float dynamiclightattenuation_b[NUM_LIGHTS];
    //float dynamiclightattenuation_c[NUM_LIGHTS]; 
};

struct LightBase
{
    float3 lightpos;
    float radius;
    float3 lightcolor;
    float strength;
};


cbuffer cposbuffer : register(b3)
{
    LightBase lights[NUM_LIGHTS];
};

struct VS_INPUT
{
	float3 position : POSITION;
    float3 normal : NORMAL;
	float3 color : COLOR;
	float3 texcoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
    float4 normal : NORMAL;
	float3 color : COLOR;
	float3 texcoord : TEXCOORD;
    float4 worldpos : WORLD_POSITION;
};

Texture2D objTexture : TEXTURE: register(t0);
SamplerState objSamplerState : SAMPLER: register(s0);

VS_OUTPUT vsmain(VS_INPUT input)
{
	
	VS_OUTPUT output = (VS_OUTPUT)0;
    output.position = mul(float4(input.position, 1.0f), wvpMatrix);
	output.color = input.color;
	output.texcoord = input.texcoord;
    output.normal = normalize(mul(float4(input.normal, 0.0f), worldMatrix));
    output.worldpos = mul(input.position, worldMatrix);
    return output;
}

 float4 psmain(VS_OUTPUT input) : SV_Target
 {
    //float3 pixelcolor = input.normal;

    
	float3 pixelcolor = objTexture.Sample(objSamplerState,input.texcoord);
    
    float3 lightc = lightcolor * lightstrength;
    float4 lightpos;
    float3 appliedlight = lightc;

    for (int i = 0; i < NUM_LIGHTS; i++)
    {
        //lightpos = mul(float4(lights[i].lightpos, 1.0f), worldMatrix);

        float3 vectortolight = normalize(lights[i].lightpos - input.worldpos);

        float3 diffuseintensity = max(dot(vectortolight, input.normal), 0);

        float distancetolight = distance(lights[i].lightpos, input.worldpos); //input.worldpos);

        float attenuationFactor = (1.0f + lights[i].radius) / (1.0f + 0.5f * distancetolight + 0.1f * pow(distancetolight, 2));

        diffuseintensity *= attenuationFactor;

        float3 diffuselight = diffuseintensity * lights[i].strength * lights[i].lightcolor;

        appliedlight += diffuselight;
   }


    float3 finalc = pixelcolor * appliedlight;
    return float4(finalc, alpha);
}
