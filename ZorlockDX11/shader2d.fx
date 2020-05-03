cbuffer cvertbuffer : register(b0)
{
	float4x4 wvpMatrix;
    float4x4 worldMatrix;
};
/*
add alpha later on
cbuffer cpixbuffer : register(b1)
{
	float alpha;

};
*/

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
    float3 normal : NORMAL;
	float3 color : COLOR;
	float3 texcoord : TEXCOORD;

};

Texture2D objTexture : TEXTURE: register(t0);
SamplerState objSamplerState : SAMPLER: register(s0);

VS_OUTPUT vsmain(VS_INPUT input)
{
	
	VS_OUTPUT output = (VS_OUTPUT)0;
    output.position = mul(float4(input.position, 1.0f), wvpMatrix);
	output.color = input.color;
	output.texcoord = input.texcoord;
    output.normal = input.normal;
    return output;
}

 float4 psmain(VS_OUTPUT input) : SV_Target
 {
 
    float4 pixelcolor = objTexture.Sample(objSamplerState, input.texcoord);

    return pixelcolor;
}
