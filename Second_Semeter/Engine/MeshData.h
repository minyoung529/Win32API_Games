#pragma once
#include "Object.h"

class Mesh;
class Material;
class GameObject;

struct MeshRenderInfo
{
	shared_ptr<Mesh>				mesh;
	vector<shared_ptr<Material>>	materials;
};

class MeshData : public Object
{
public:
	MeshData();
	virtual ~MeshData();

public:
	static shared_ptr<MeshData> LoadFromFBX(const wstring& path);
	vector<shared_ptr<GameObject>> Instantiate();

private:
	shared_ptr<Mesh>				m_mesh;
	vector<shared_ptr<Material>>	m_materials;
	vector<MeshRenderInfo>			m_meshRenders;
};