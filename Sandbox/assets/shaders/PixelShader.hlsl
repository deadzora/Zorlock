cbuffer cpixbuffer : register(b1)
{
    float alpha;
};
struct VS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 texcoord : TEXCOORD;
};
Texture2D objTexture : TEXTURE : register(t0);
SamplerState objSamplerState : SAMPLER : register(s0);

float main(VS_INPUT input) : SV_Target
{
    float3 pixelcolor = objTexture.Sample(objSamplerState, input.texcoord);
    return float4(pixelcolor, alpha);
}