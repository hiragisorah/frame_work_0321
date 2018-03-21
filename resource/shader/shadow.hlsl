Texture2D g_tex : register(t0);
SamplerState g_sampler : register(s0);

cbuffer global
{
    matrix g_w;
    matrix g_v;
    matrix g_p;

    float4 g_lightdir;
    float4 g_diffuse;
};

//バーテックスバッファー出力構造体
struct VS_OUTPUT
{
    float4 position_ : SV_POSITION;
    float4 color_ : COLOR0;
    float3 light_ : TEXCOORD0;
    float3 normal_ : TEXCOORD1;
    float2 uv_ : TEXCOORD2;
};

VS_OUTPUT VS(float4 position : POSITION, float4 normal : NORMAL, float2 uv : TEXCOORD)
{
    matrix wvp = transpose(mul(g_p, mul(g_v, g_w)));
    matrix w = transpose(g_w);

    VS_OUTPUT output = (VS_OUTPUT) 0;
	
    output.normal_ = mul(normal, (float3x3)w);
    output.position_ = mul(position, wvp);
    output.light_ = g_lightdir;

    float3 _normal = normalize(output.normal_);
    float3 _light_dir = normalize(output.light_);
    float4 nl = saturate(dot(_normal, _light_dir));

    float3 reflect = normalize(2 * nl * _normal - _light_dir);

    output.color_ = g_diffuse * nl;
    output.color_.a = 1.f;
    output.uv_ = uv;

    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color = g_tex.Sample( g_sampler, input.uv_ );
    color *= input.color_ * 2;
	return color;
}