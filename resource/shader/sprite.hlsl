//グローバル

Texture2D g_tex: register(t0);//テクスチャーは レジスターt(n)
SamplerState g_sampler : register(s0);//サンプラーはレジスターs(n)

cbuffer global
{
	matrix g_w; //ワールドから射影までの変換行列
	matrix g_v; //ワールドから射影までの変換行列
    matrix g_p; //ワールドから射影までの変換行列

	float4 g_diffuse;//ディフューズ色
};

//構造体
struct VS_OUTPUT
{
	float4 position_ : SV_POSITION;
	float2 uv_ : TEXCOORD;
};

//
//バーテックスシェーダー
//
VS_OUTPUT VS( float4 position : POSITION ,float2 uv : TEXCOORD )
{
    matrix wvp = transpose(mul(g_p, mul(g_v, g_w)));

	VS_OUTPUT output = (VS_OUTPUT)0;

	output.position_ = mul(position, wvp);
	output.uv_ = uv;

	return output;
}

//
//ピクセルシェーダー
//
float4 PS( VS_OUTPUT input  ) : SV_Target
{
	return g_tex.Sample( g_sampler, input.uv_ ) * g_diffuse;
}