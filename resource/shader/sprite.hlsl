//�O���[�o��

Texture2D g_tex: register(t0);//�e�N�X�`���[�� ���W�X�^�[t(n)
SamplerState g_sampler : register(s0);//�T���v���[�̓��W�X�^�[s(n)

cbuffer global
{
	matrix g_w; //���[���h����ˉe�܂ł̕ϊ��s��
	matrix g_v; //���[���h����ˉe�܂ł̕ϊ��s��
    matrix g_p; //���[���h����ˉe�܂ł̕ϊ��s��

	float4 g_diffuse;//�f�B�t���[�Y�F
};

//�\����
struct VS_OUTPUT
{
	float4 position_ : SV_POSITION;
	float2 uv_ : TEXCOORD;
};

//
//�o�[�e�b�N�X�V�F�[�_�[
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
//�s�N�Z���V�F�[�_�[
//
float4 PS( VS_OUTPUT input  ) : SV_Target
{
	return g_tex.Sample( g_sampler, input.uv_ ) * g_diffuse;
}