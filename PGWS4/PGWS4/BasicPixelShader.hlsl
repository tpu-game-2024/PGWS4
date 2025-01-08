#include "BasicShaderHeader.hlsli"

float4 BasicPS(Output input) : SV_TARGET
{
    //float3 light = normalize(float3(1, -1, 1));
    
    // ƒ‰ƒCƒg‚ð‰ñ“]‚³‚¹‚é
    float angle = time_mat; // ŽžŠÔ‚É‰ž‚¶‚½‰ñ“]Šp“x
    float3 light = normalize(float3(0, 0, 1));
//    float3 light = normalize(float3(1, -1, 1));

    
    float brightness = max(dot(-light, normalize(input.normal.xyz)), 0) * 0.9 + 0.1;
    return float4(brightness, brightness, brightness, 1);
}