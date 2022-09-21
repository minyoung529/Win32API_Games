// GPU�� �������͸� ���ڴ�
// b0 => ��� ������ �ε��� ����
// ��Ʈ �ñ״�ó
cbuffer TEST_B0 : register(b0)
{
    float3 offset0;
};

struct VS_IN
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    // GPU�� ������ �ؼ� ������
    input.pos += offset0;
    output.pos = float4(input.pos, 1.f);
    //output.pos += float4(offset0, 1.f);
    output.color = input.color;

    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    return input.color;
}