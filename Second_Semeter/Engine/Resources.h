#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class Resources
{
	DECLARE_SINGLE(Resources);

public:
	void Init();

private:
	void CreatDefaultShader();

public:
	// �ؽ��� �����
	shared_ptr<Texture> CreateTexture(const wstring& name, DXGI_FORMAT format, uint32 width,
		uint32 height,
		const D3D12_HEAP_PROPERTIES& heapProperty, D3D12_HEAP_FLAGS heapFlags,
		D3D12_RESOURCE_FLAGS resFlags = D3D12_RESOURCE_FLAG_NONE, Vec4 clearColor = Vec4());

	shared_ptr<Texture> CreateTextureFromResource(const wstring& name,
		ComPtr<ID3D12Resource> tex2D);


public:
	template<typename T>
	shared_ptr<T> Load(const wstring& key, const wstring& path);

	template<typename T>
	bool Add(const wstring& key, shared_ptr<T> object);

	template<typename T>
	shared_ptr<T> Get(const wstring& key);

	template<typename T>
	OBJECT_TYPE GetObjectType();

public:
	shared_ptr<Mesh> LoadCubeMesh();
	shared_ptr<Mesh> LoadSphereMesh();
	shared_ptr<Mesh> LoadQuadMesh();
	shared_ptr<Mesh> LoadPlaneMesh(float width, float depth, uint32 m, uint32 n);
	shared_ptr<Mesh> LoadMeshFile(const wstring& path, const wstring& name);
	shared_ptr<Mesh> LoadTerrainMesh(int32 sizeX = 15, int32 SizeZ = 15);
	
	shared_ptr<class MeshData> LoadFBX(const wstring& path);

private:
	using KeyObjMap = std::map<wstring/*Key*/, shared_ptr<Object>>;
	array<KeyObjMap, OBJECT_TYPE_COUNT> m_resources;
};

template<typename T>
shared_ptr<T> Resources::Load(const wstring& key, const wstring& path)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = m_resources[static_cast<uint8>(objectType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return static_pointer_cast<T>(findIt->second);

	shared_ptr<T> object = make_shared<T>();
	object->Load(path);
	keyObjMap[key] = object;

	return object;
}

template<typename T>
bool Resources::Add(const wstring& key, shared_ptr<T> object)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = m_resources[static_cast<uint8>(objectType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
	{
		return false;
	}

	keyObjMap[key] = object;

	return true;
}

template<typename T>
shared_ptr<T> Resources::Get(const wstring& key)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = m_resources[static_cast<uint8>(objectType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return static_pointer_cast<T>(findIt->second);

	return nullptr;
}

template<typename T>
OBJECT_TYPE Resources::GetObjectType()
{
	if (std::is_same_v<T, GameObject>)
		return OBJECT_TYPE::GAMEOBJECT;
	else if (std::is_same_v<T, Component>)
		return OBJECT_TYPE::COMPONENT;
	else if (std::is_same_v<T, Material>)
		return OBJECT_TYPE::MATERIAL;
	else if (std::is_same_v<T, Mesh>)
		return OBJECT_TYPE::MESH;
	else if (std::is_same_v<T, Shader>)
		return OBJECT_TYPE::SHADER;
	else if (std::is_same_v<T, Texture>)
		return OBJECT_TYPE::TEXTURE;
	else
		return OBJECT_TYPE::NONE;
}