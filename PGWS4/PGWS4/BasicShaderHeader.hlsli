struct Output
{
    float4 svpos : SV_POSITION;
    float4 normal : NORMAL; //ñ@ê¸vec
    float2 uv : TEXCOORD;
};

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

cbuffer cbuff0 : register(b0)
{
    matrix mat;
};