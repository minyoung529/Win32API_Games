#ifndef _TERRAIN_HLSLI_
#define _TERRAIN_HLSLI_

#include "Params.hlsl"
#include "Utils.hlsl"

// --------------
// Vertex Shader
// --------------

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

// 도메인 셰이더 때문에
// 연산 X
VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = input;
    return output;
}


// --------------
// Hull Shader
// --------------

struct PatchTess
{
    float edgeTess[3] : SV_TessFactor;
    float insideTess : SV_InsideTessFactor;
};

struct HS_OUT
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

// Constant HS
PatchTess ConstantHS(InputPatch<VS_OUT, 3> input, int patchID : SV_PrimitiveID)
{
    PatchTess output = (PatchTess) 0.f;

    float minDistance = vec2_1.x;
    float maxDistance = vec2_1.y;

    // 0 1 2
    float3 edge0Pos = (input[1].pos + input[2].pos) / 2.f;
    float3 edge1Pos = (input[2].pos + input[0].pos) / 2.f;
    float3 edge2Pos = (input[0].pos + input[1].pos) / 2.f;

    edge0Pos = mul(float4(edge0Pos, 1.f), matWorld).xyz;
    edge1Pos = mul(float4(edge1Pos, 1.f), matWorld).xyz;
    edge2Pos = mul(float4(edge2Pos, 1.f), matWorld).xyz;

    float edge0TessLevel = CalculateTessLevel(vec4_0.xyz, edge0Pos, minDistance, maxDistance, 4.f);
    float edge1TessLevel = CalculateTessLevel(vec4_0.xyz, edge1Pos, minDistance, maxDistance, 4.f);
    float edge2TessLevel = CalculateTessLevel(vec4_0.xyz, edge2Pos, minDistance, maxDistance, 4.f);

    output.edgeTess[0] = edge0TessLevel;
    output.edgeTess[1] = edge1TessLevel;
    output.edgeTess[2] = edge2TessLevel;
    output.insideTess = edge2TessLevel;

    return output;
}

// Control Point HS
[domain("tri")] // 패치의 종류 (tri, quad, isoline) 
[partitioning("fractional_odd")] // subdivision mode (integer 소수점 무시, fractional_even, fractional_odd)
[outputtopology("triangle_cw")] // (triangle_cw, triangle_ccw, line)
[outputcontrolpoints(3)] // 하나의 입력 패치에 대해, HS가 출력할 제어점 개수 > 3개의 control point
[patchconstantfunc("ConstantHS")] // ConstantHS 함수 이름 (정점 개수 늘리는 함수)
HS_OUT HS_Main(InputPatch<VS_OUT, 3> input, int vertexIdx : SV_OutputControlPointID, int patchID : SV_PrimitiveID)
{
    HS_OUT output = (HS_OUT) 0.f;

    output.pos = input[vertexIdx].pos;
    output.uv = input[vertexIdx].uv;
    return output;
}

// --------------
// Domain Shader
// --------------
struct DS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
    float3 viewPos : POSITION;
    float3 viewNormal : NORMAL;
    float3 viewTangent : TANGENT;
    float3 viewBinormal : BINORMAL;
};

[domain("tri")]
DS_OUT DS_Main(const OutputPatch<HS_OUT, 3> input, float3 location : SV_DomainLocation, PatchTess patch)
{
    DS_OUT output = (DS_OUT) 0.f;
    float3 localPos = input[0].pos * location[0] + input[1].pos * location[1] + input[2].pos * location[2];
    float2 uv = input[0].uv * location[0] + input[1].uv * location[1] + input[2].uv * location[2];

    int tileCountX = int_0;
    int tileCountZ = int_1;
    int mapWidth = vec2_0.x;
    int mapHeight = vec2_0.y;

    // 높이맵 높이 적용
    // uv를 뽑아온다
    float2 fullUV = float2(uv.x / (float) tileCountX, uv.y / (float) tileCountZ);
    float height = tex_2.SampleLevel(sam_0, fullUV, 0).x;
    localPos.y = height*10; 
    // 실제로 정점의 높이가 바뀐다!

    float2 deltaUV = float2(1.f / mapWidth, 1.f / mapHeight);
    float2 deltaPos = float2(tileCountX * deltaUV.x, tileCountZ * deltaUV.y);

    float upHeight      = tex_2.SampleLevel(sam_0, float2(fullUV.x, fullUV.y - deltaUV.y), 0).x;
    float downHeight    = tex_2.SampleLevel(sam_0, float2(fullUV.x, fullUV.y + deltaUV.y), 0).x;
    float rightHeight   = tex_2.SampleLevel(sam_0, float2(fullUV.x + deltaUV.x, fullUV.y), 0).x;
    float leftHeight    = tex_2.SampleLevel(sam_0, float2(fullUV.x - deltaUV.x, fullUV.y), 0).x;

    float3 localTangent = float3(localPos.x + deltaPos.x, rightHeight, localPos.z) - float3(localPos.x - deltaPos.x, leftHeight, localPos.z);
    float3 localBinormal = float3(localPos.x, upHeight, localPos.z + deltaPos.y) - float3(localPos.x, downHeight, localPos.z - deltaPos.y);

    output.pos = mul(float4(localPos, 1.f), matWVP);
    output.viewPos = mul(float4(localPos, 1.f), matWV).xyz;

    output.viewTangent = normalize(mul(float4(localTangent, 0.f), matWV)).xyz;
    output.viewBinormal = normalize(mul(float4(localBinormal, 0.f), matWV)).xyz;
    output.viewNormal = normalize(cross(output.viewBinormal, output.viewTangent));

    output.uv = uv;
    return output;
}

// --------------
// Pixel Shader
// --------------

// VS_OUT => DS_OUT
float4 PS_Main(DS_OUT input) : SV_Target
{
    float4 color = float4(1.f, 1.f, 1.f, 1.f);
    if (tex_on_0)
        color = tex_0.Sample(sam_0, input.uv);

    float3 viewNormal = input.viewNormal;
    if (tex_on_1)
    {
        // [0,255] 범위에서 [0,1]로 변환
        float3 tangentSpaceNormal = tex_1.Sample(sam_0, input.uv).xyz;
        // [0,1] 범위에서 [-1,1]로 변환
        tangentSpaceNormal = (tangentSpaceNormal - 0.5f) * 2.f;
        float3x3 matTBN = { input.viewTangent, input.viewBinormal, input.viewNormal };
        viewNormal = normalize(mul(tangentSpaceNormal, matTBN));
    }

    LightColor totalColor = (LightColor) 0.f;

    for (int i = 0; i < g_lightCount; ++i)
    {
        LightColor color = CalculateLightColor(i, viewNormal, input.viewPos);
        totalColor.diffuse += color.diffuse;
        totalColor.ambient += color.ambient;
        totalColor.specular += color.specular;
    }

    color.xyz = (totalColor.diffuse.xyz * color.xyz)
        + totalColor.ambient.xyz * color.xyz
        + totalColor.specular.xyz;

    return color;
}
#endif // _TERRAIN_HLSLI_
