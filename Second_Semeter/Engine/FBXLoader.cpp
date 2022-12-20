#include "pch.h"
#include "FBXLoader.h"
#include "Mesh.h"
#include "Resources.h"
#include "Shader.h"
#include "Material.h"
#include "Texture.h"

FBXLoader::FBXLoader()
{
}

FBXLoader::~FBXLoader()
{
	if (m_scene)
		m_scene->Destroy();
	if (m_manager)
		m_manager->Destroy();
}

void FBXLoader::LoadFbx(const wstring& path)
{
	// 파일 데이터 로드
	Import(path);

	// 로드된 데이터 파싱 (Mesh/Material/Skin)
	ParseNode(m_scene->GetRootNode());

	CreateTextures();
	CreateMaterials();
}

void FBXLoader::Import(const wstring& path)
{
	m_manager = FbxManager::Create(); // FBX SDK 관리자 객체 생성

	// IOSettings 객체 생성 및 설정
	FbxIOSettings* settings = FbxIOSettings::Create(m_manager, IOSROOT);
	m_manager->SetIOSettings(settings);

	// FbxImporter 객체 생성
	m_scene = FbxScene::Create(m_manager, "");

	// 나중에 Texture 경로 계산할 때 쓸 것
	m_resourceDirectory = fs::path(path).parent_path().wstring() + L"\\" + fs::path(path).filename().stem().wstring() + L".fbm";

	m_importer = FbxImporter::Create(m_manager, "");

	string strPath = ws2s(path);
	m_importer->Initialize(strPath.c_str(), -1, m_manager->GetIOSettings());

	m_importer->Import(m_scene);

	m_scene->GetGlobalSettings().SetAxisSystem(FbxAxisSystem::DirectX);

	// 씬 내에서 삼각형화 할 수 있는 모든 노드를 삼각형화 시킨다.
	FbxGeometryConverter geometryConverter(m_manager);
	geometryConverter.Triangulate(m_scene, true);

	m_importer->Destroy();
}
void FBXLoader::ParseNode(FbxNode* node)
{
	FbxNodeAttribute* attribute = node->GetNodeAttribute();

	if (attribute)
	{
		switch (attribute->GetAttributeType())
		{
		case FbxNodeAttribute::eMesh:
			LoadMesh(node->GetMesh());
			break;
		}
	}

	// Material 로드
	const uint32 materialCount = node->GetMaterialCount();
	for (uint32 i = 0; i < materialCount; ++i)
	{
		FbxSurfaceMaterial* surfaceMaterial = node->GetMaterial(i);
		LoadMaterial(surfaceMaterial);
	}

	// Tree 구조 재귀 호출
	const int32 childCount = node->GetChildCount();
	for (int32 i = 0; i < childCount; ++i)
		ParseNode(node->GetChild(i));
}

void FBXLoader::LoadMesh(FbxMesh* mesh)
{
	m_meshes.push_back(FbxMeshInfo());
	FbxMeshInfo& meshInfo = m_meshes.back();

	meshInfo.name = s2ws(mesh->GetName());

	const int32 vertexCount = mesh->GetControlPointsCount();
	meshInfo.vertices.resize(vertexCount);

	// Position
	FbxVector4* controlPoints = mesh->GetControlPoints();
	for (int32 i = 0; i < vertexCount; ++i)
	{
		meshInfo.vertices[i].pos.x = static_cast<float>(controlPoints[i].mData[0]);
		meshInfo.vertices[i].pos.y = static_cast<float>(controlPoints[i].mData[2]);
		meshInfo.vertices[i].pos.z = static_cast<float>(controlPoints[i].mData[1]);
	}

	const int32 materialCount = mesh->GetNode()->GetMaterialCount();
	meshInfo.indices.resize(materialCount);

	FbxGeometryElementMaterial* geometryElementMaterial = mesh->GetElementMaterial();

	const int32 polygonSize = mesh->GetPolygonSize(0);
	assert(polygonSize == 3);

	uint32 arrIdx[3];
	uint32 vertexCounter = 0; // 정점의 개수

	const int32 triCount = mesh->GetPolygonCount(); // 메쉬의 삼각형 개수를 가져온다
	for (int32 i = 0; i < triCount; i++) // 삼각형의 개수
	{
		for (int32 j = 0; j < 3; j++) // 삼각형은 세 개의 정점으로 구성
		{
			int32 controlPointIndex = mesh->GetPolygonVertex(i, j); // 제어점 인덱스추출
			arrIdx[j] = controlPointIndex;

			GetNormal(mesh, &meshInfo, controlPointIndex, vertexCounter);
			GetTangent(mesh, &meshInfo, controlPointIndex, vertexCounter);
			GetUV(mesh, &meshInfo, controlPointIndex, mesh->GetTextureUVIndex(i, j));

			vertexCounter++;
		}

		const uint32 subsetIdx = geometryElementMaterial->GetIndexArray().GetAt(i);
		meshInfo.indices[subsetIdx].push_back(arrIdx[0]);
		meshInfo.indices[subsetIdx].push_back(arrIdx[2]);
		meshInfo.indices[subsetIdx].push_back(arrIdx[1]);
	}
}

void FBXLoader::LoadMaterial(FbxSurfaceMaterial* surfaceMaterial)
{
	FbxMaterialInfo material{};
	material.name = s2ws(surfaceMaterial->GetName());

	material.diffuse = GetMaterialData(surfaceMaterial, FbxSurfaceMaterial::sDiffuse, FbxSurfaceMaterial::sDiffuseFactor);
	material.ambient = GetMaterialData(surfaceMaterial, FbxSurfaceMaterial::sAmbient, FbxSurfaceMaterial::sAmbientFactor);
	material.specular = GetMaterialData(surfaceMaterial, FbxSurfaceMaterial::sSpecular, FbxSurfaceMaterial::sSpecularFactor);

	material.diffuseTexName = GetTextureRelativeName(surfaceMaterial, FbxSurfaceMaterial::sDiffuse);
	material.normalTexName = GetTextureRelativeName(surfaceMaterial, FbxSurfaceMaterial::sNormalMap);
	material.specularTexName = GetTextureRelativeName(surfaceMaterial, FbxSurfaceMaterial::sSpecular);

	m_meshes.back().materials.push_back(material);
}

void FBXLoader::GetNormal(FbxMesh* mesh, FbxMeshInfo* container, int32 idx, int32 vertexCounter)
{
	if (mesh->GetElementNormalCount() == 0)
		return;

	FbxGeometryElementNormal* normal = mesh->GetElementNormal();
	uint32 normalIdx = 0;

	if (normal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		if (normal->GetReferenceMode() == FbxGeometryElement::eDirect)
			normalIdx = vertexCounter;
		else
			normalIdx = normal->GetIndexArray().GetAt(vertexCounter);
	}
	else if (normal->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (normal->GetReferenceMode() == FbxGeometryElement::eDirect)
			normalIdx = idx;
		else
			normalIdx = normal->GetIndexArray().GetAt(idx);
	}

	FbxVector4 vec = normal->GetDirectArray().GetAt(normalIdx);
	container->vertices[idx].normal.x = static_cast<float>(vec.mData[0]);
	container->vertices[idx].normal.y = static_cast<float>(vec.mData[2]);
	container->vertices[idx].normal.z = static_cast<float>(vec.mData[1]);
}
void FBXLoader::GetTangent(FbxMesh* mesh, FbxMeshInfo* meshInfo, int32 idx, int32 vertexCounter)
{
	if (mesh->GetElementTangentCount() == 0)
	{
		meshInfo->vertices[idx].tangent.x = 1.f;
		meshInfo->vertices[idx].tangent.y = 0.f;
		meshInfo->vertices[idx].tangent.z = 0.f;
		return;
	}

	FbxGeometryElementTangent* tangent = mesh->GetElementTangent();
	uint32 tangentIdx = 0;

	if (tangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		if (tangent->GetReferenceMode() == FbxGeometryElement::eDirect)
			tangentIdx = vertexCounter;
		else
			tangentIdx = tangent->GetIndexArray().GetAt(vertexCounter);
	}
	else if (tangent->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (tangent->GetReferenceMode() == FbxGeometryElement::eDirect)
			tangentIdx = idx;
		else
			tangentIdx = tangent->GetIndexArray().GetAt(idx);
	}

	FbxVector4 vec = tangent->GetDirectArray().GetAt(tangentIdx);
	meshInfo->vertices[idx].tangent.x = static_cast<float>(vec.mData[0]);
	meshInfo->vertices[idx].tangent.y = static_cast<float>(vec.mData[2]);
	meshInfo->vertices[idx].tangent.z = static_cast<float>(vec.mData[1]);
}

void FBXLoader::GetUV(FbxMesh* mesh, FbxMeshInfo* meshInfo, int32 idx, int32 uvIndex)
{
	FbxVector2 uv = mesh->GetElementUV()->GetDirectArray().GetAt(uvIndex);
	meshInfo->vertices[idx].uv.x = static_cast<float>(uv.mData[0]);
	meshInfo->vertices[idx].uv.y = 1.f - static_cast<float>(uv.mData[1]);
}

Vec4 FBXLoader::GetMaterialData(FbxSurfaceMaterial* surface, const char* materialName, const char* factorName)
{
	FbxDouble3  material;
	FbxDouble   factor = 0.f;
	FbxProperty materialProperty = surface->FindProperty(materialName);
	FbxProperty factorProperty = surface->FindProperty(factorName);

	if (materialProperty.IsValid() && factorProperty.IsValid())
	{
		material = materialProperty.Get<FbxDouble3>();
		factor = factorProperty.Get<FbxDouble>();
	}

	Vec4 ret = Vec4(
		static_cast<float>(material.mData[0] * factor),
		static_cast<float>(material.mData[1] * factor),
		static_cast<float>(material.mData[2] * factor),
		static_cast<float>(factor));

	return ret;
}

wstring FBXLoader::GetTextureRelativeName(FbxSurfaceMaterial* surface, const char* materialProperty)
{
	string name;

	FbxProperty textureProperty = surface->FindProperty(materialProperty);
	if (textureProperty.IsValid())
	{
		uint32 count = textureProperty.GetSrcObjectCount();

		if (1 <= count)
		{
			FbxFileTexture* texture = textureProperty.GetSrcObject<FbxFileTexture>(0);
			if (texture)
				name = texture->GetRelativeFileName();
		}
	}

	return s2ws(name);
}

void FBXLoader::CreateTextures()
{
	for (size_t i = 0; i < m_meshes.size(); ++i)
	{
		for (size_t j = 0; j < m_meshes[i].materials.size(); ++j)
		{
			// Diffuse Texture
			{
				wstring relativePath = m_meshes[i].materials[j].diffuseTexName.c_str();
				wstring filename = fs::path(relativePath).filename();
				wstring fullPath = m_resourceDirectory + L"\\" + filename;

				if (!filename.empty())
					GET_SINGLE(Resources)->Load<Texture>(filename, fullPath);
			}

			// Normal Texture
			{
				wstring relativePath = m_meshes[i].materials[j].normalTexName.c_str();
				wstring filename = fs::path(relativePath).filename();
				wstring fullPath = m_resourceDirectory + L"\\" + filename;

				if (!filename.empty())
					GET_SINGLE(Resources)->Load<Texture>(filename, fullPath);
			}

			// Normal Texture
			{
				wstring relativePath = m_meshes[i].materials[j].specularTexName.c_str();
				wstring filename = fs::path(relativePath).filename();
				wstring fullPath = m_resourceDirectory + L"\\" + filename;

				if (!filename.empty())
					GET_SINGLE(Resources)->Load<Texture>(filename, fullPath);
			}
		}
	}
}

void FBXLoader::CreateMaterials()
{
	for (size_t i = 0; i < m_meshes.size(); ++i)
	{
		for (size_t j = 0; j < m_meshes[i].materials.size(); ++j)
		{
			shared_ptr<Material> material = make_shared<Material>();
			wstring key = m_meshes[i].materials[j].name;
			material->SetName(key);
			material->SetShader(GET_SINGLE(Resources)->Get<Shader>(L"Default"));

			{   // Diffuse
				wstring diffuseName = m_meshes[i].materials[j].diffuseTexName.c_str();
				wstring filename = fs::path(diffuseName).filename();
				wstring key = filename;
				shared_ptr<Texture> diffuseTexture = GET_SINGLE(Resources)->Get<Texture>(key);

				if (diffuseTexture)
				{
					material->SetTexture(0, diffuseTexture);
				}
			}

			{   // Normal
				wstring name = m_meshes[i].materials[j].normalTexName.c_str();
				wstring filename = fs::path(name).filename();
				wstring key = filename;
				shared_ptr<Texture> normalTexture = GET_SINGLE(Resources)->Get<Texture>(key);

				if (normalTexture)
				{
					material->SetTexture(1, normalTexture);
				}
			}


			{   // Specular
				wstring name = m_meshes[i].materials[j].specularTexName.c_str();
				wstring filename = fs::path(name).filename();
				wstring key = filename;
				shared_ptr<Texture> specularTexture = GET_SINGLE(Resources)->Get<Texture>(key);

				if (specularTexture)
				{
					material->SetTexture(2, specularTexture);
				}
			}

			GET_SINGLE(Resources)->Add<Material>(material->GetName(), material);
		}
	}
}
