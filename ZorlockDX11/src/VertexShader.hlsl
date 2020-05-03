cbuffer cvertbuffer : register(b0)
{
    float4x4 mat;
};
struct VS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;
    float3 texcoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 texcoord : TEXCOORD;
};


VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    output.position = mul(input.position, mat);
    output.color = input.color;
    output.texcoord = input.texcoord;
    return output;
}