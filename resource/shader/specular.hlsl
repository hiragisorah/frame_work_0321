//�O���[�o��
cbuffer global
{
    matrix g_w; //���[���h�s��
    matrix g_v;
    matrix g_p;

    float4 g_vLightDir; //���C�g�̕����x�N�g��
	float4 g_Diffuse; //�g�U����(�F�j	
    float4 g_vEye; //�J�����i���_�j
};

//�\����
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 Light : TEXCOORD0;
    float3 Normal : TEXCOORD1;
    float3 EyeVector : TEXCOORD2;
};

//
//�o�[�e�b�N�X�V�F�[�_�[
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
//�s�N�Z���V�F�[�_�[
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