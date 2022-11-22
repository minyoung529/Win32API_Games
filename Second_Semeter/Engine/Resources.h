#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

class Resources
{
	DECLARE_SINGLE(Resources)

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

private:
	using KeyObjMap = std::map<wstring, shared_ptr<Object>>;
	array<KeyObjMap, OBJECT_TYPE_COUNT> m_resources;
};

template<typename T>
shared_ptr<T> Resources::Load(const wstring& key, const wstring& path)
{
	OBJECT_TYPE objType = GetObjectType();
	KeyObjMap& keyObjMap = m_resources[static_cast<uint8>(objType)];

	auto findIt = keyObjMap.find(objType);

	if (findIt != keyObjMap.end())
	{
		return static_pointer_cast<T>(findIt->second);
	}

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

	if (std::is_same_v<T, Shader>)
		return OBJECT_TYPE::SHADER;

	if (std::is_same_v<T, Mesh>)
		return OBJECT_TYPE::MESH;

	if (std::is_same_v<T, Texture>)
		return OBJECT_TYPE::TEXTURE;

	if (std::is_same_v<T, Component>)
		return OBJECT_TYPE::COMPONENT;

	if (std::is_same_v<T, Material>)
		return OBJECT_TYPE::MATERIAL;

	return OBJECT_TYPE::NONE;
}