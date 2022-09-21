// GPU의 레지스터를 쓰겠다
// b0 => 상수 버퍼의 인덱스 세팅
// 루트 시그니처
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

    // GPU가 연산을 해서 빠르다
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