#include "pch.h"
#include "Terrain.h"
#include "Resources.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"
#include "Transform.h"
#include "MeshRenderer.h"

Terrain::Terrain() : Component(COMPONENT_TYPE::TERRAIN)
{
}

Terrain::~Terrain()
{
}

// [Terrain Shader]
// int_0	: TileX
// int_1	: TileZ
// float_0	: Max Tesselation Level
// Vec2_0	: HeightMap Resolution
// Vec2_1	: Min/Max Tesselation distance
// Vec4_0	: Camera Position
// tex_0	: Diffuse Texture
// tex_1	: Normal Texture
// tex_2	: HeightMap Texture

void Terrain::Init(int32 sizeX, int32 sizeZ)
{
	m_sizeX = sizeX;
	m_sizeZ = sizeZ;

	m_material = make_shared<Material>();

	shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Terrain");
	shared_ptr<Texture> texture = GET_SINGLE(Resources)->Load<Texture>(L"Terrain", L"..\\Resources\\Texture\\Terrain.jpg");
	shared_ptr<Texture> normalTexture = GET_SINGLE(Resources)->Load<Texture>(L"Terrain_Normal", L"..\\Resources\\Texture\\Terrain_Normal.jpg");
	shared_ptr<Texture> heightTexture = GET_SINGLE(Resources)->Load<Texture>(L"Terrain_Height", L"..\\Resources\\Texture\\Terrain_Height.jpg");

	m_material->SetShader(shader);
	m_material->SetTexture(0, texture);

	m_material->SetInt(0, sizeX);
	m_material->SetInt(1, sizeZ);
	m_material->SetFloat(0, m_maxTesselation);

	m_material->SetTexture(1, normalTexture);
	m_material->SetTexture(1, normalTexture);

	m_material->SetVec2(0, Vec2(heightTexture->GetWidth(), heightTexture->GetHeight()));
	m_material->SetVec2(1, Vec2(500.f, 5000.f));

	shared_ptr<MeshRenderer> meshRenderer = GetGameObject()->GetMeshRenderer();
	shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadTerrainMesh(sizeX, sizeZ);

	meshRenderer->SetMesh(mesh);
	meshRenderer->SetMaterial(m_material);
}

void Terrain::FinalUpdate()
{
	shared_ptr<Camera> mainCam = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera();

	if (!mainCam)return;

	Vec3 pos = mainCam->GetTransform()->GetLocalPosition();
	m_material->SetVec4(0, Vec4(pos.x, pos.y, pos.z, 0));
}