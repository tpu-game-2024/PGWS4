#include "BasicShaderHeader.hlsli"

Output BasicVS( float4 pos : POSITION ,float2 uv :TEXCOORD)
{
    Output output; // ピクセルシェーダーに渡す値
    output.svpos = mul(mat,pos);
    //output.svpos = pos;
    output.uv = uv;
    return output;
}
