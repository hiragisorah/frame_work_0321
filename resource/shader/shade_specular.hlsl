cbuffer global
{
    matrix g_w;
    matrix g_v;
    matrix g_p;

    float4 g_light_dir;
    float4 g_diffuse;
    float4 g_eye;
};

struct VS_OUTPUT
{
    float4 position_ : SV_POSITION;
    float3 light_ : TEXCOORD0;
    float3 normal_ : TEXCOORD1;
    float3 eye_vector_ : TEXCOORD2;
};

VS_OUTPUT VS(float4 position : POSITION, float4 normal : NORMAL)
{
    matrix wvp = transpose(mul(g_p, mul(g_v, g_w)));
    matrix w = transpose(g_w);

    VS_OUTPUT output = (VS_OUTPUT) 0;

    output.position_ = mul(position, wvp);
    output.normal_ = mul(normal, (float3x3) w);
    output.light_ = normalize(g_light_dir);

    float3 position_world = output.position_;
    output.eye_vector_ = g_eye - position_world;
	
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float3 normal = normalize(input.normal_);
    float3 light_dir = normalize(input.light_);
    float3 view_dir = normalize(input.eye_vector_);
    float4 nl = saturate(dot(normal, light_dir));

    float3 reflect = normalize(2 * nl * normal - light_dir);
    float4 specular = 2 * pow(saturate(dot(reflect, view_dir)), 2);

    return g_diffuse * specular;
}