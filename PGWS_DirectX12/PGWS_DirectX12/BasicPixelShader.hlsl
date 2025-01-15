#include "BasicShaderHeader.hlsli"

float4 BasicPS(Output input) : SV_TARGET
{
    float3 light = normalize(float3(1, -1, 1));
    float brightness = dot(-light, input.normal);
    return float4(brightness,brightness,brightness,1);
}


//#include"BasicType.hlsli"

//Texture2D<float4> tex : register(t0);
//SamplerState smp : register(s0);

//float4 BasicPS(BasicType input) : SV_TARGET
//{
//    return float4(tex.Sample(smp, input.uv));
//}