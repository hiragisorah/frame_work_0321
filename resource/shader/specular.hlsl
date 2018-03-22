//グローバル
cbuffer global
{
    matrix g_w; //ワールド行列
    matrix g_v;
    matrix g_p;

    float4 g_vLightDir; //ライトの方向ベクトル
	float4 g_Diffuse; //拡散反射(色）	
    float4 g_vEye; //カメラ（視点）
};

//構造体
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 Light : TEXCOORD0;
    float3 Normal : TEXCOORD1;
    float3 EyeVector : TEXCOORD2;
};

//
//バーテックスシェーダー
//
VS_OUTPUT VS(float4 Pos : POSITION, float4 Normal : NORMAL)
{
    matrix wvp = transpose(mul(g_p, mul(g_v, g_w)));
    matrix w = transpose(g_w);

    VS_OUTPUT output = (VS_OUTPUT) 0;

    output.Pos = mul(Pos, wvp);
    output.Normal = mul(Normal, (float3x3) w);
    output.Light = normalize(g_vLightDir);

    float3 PosWorld = mul(Pos, w);
    output.EyeVector = g_vEye - PosWorld;

    return output;
}

//
//ピクセルシェーダー
//
float4 PS(VS_OUTPUT input) : SV_Target
{
    float3 Normal = normalize(input.Normal);
    float3 LightDir = normalize(input.Light);
    float3 ViewDir = normalize(input.EyeVector);
    float4 NL = saturate(dot(Normal, LightDir));

    float3 Reflect = normalize(2 * NL * Normal - LightDir);
    float4 specular = 2 * pow(saturate(dot(Reflect, ViewDir)), 2);

    return g_Diffuse * NL + specular;
}