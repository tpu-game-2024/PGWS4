#include "BasicShaderHeader.hlsli"

Output BasicVS(
    float4 pos : POSITION,
    float4 normal : NORMAL,
    float2 uv : TEXCOORD,
    min16uint2 bonebo : BONE_NO,
    min16uint weight : WEIGHT
    )
{
    Output output; // ピクセルシェーダーに渡す値
    output.svpos = mul(mul(viewproj,world),pos); // シェーダーでは列優先なので注意
    normal.w = 0; // ここが重要（平行移動成分を無効にする）
    output.normal = mul(world, normal); // 法線にもワールド変換を行う
    output.uv = uv;
    return output;
}


//#include"BasicType.hlsli"

//cbuffer cbuff0 : register(b0)
//{
//    matrix mat;
//};

//BasicType BasicVS(float4 pos : POSITION, float2 uv : TEXCOORD)
//{
//    BasicType output;
//    output.svpos = mul(mat, pos);
//    output.uv = uv;
//    return output;
//}