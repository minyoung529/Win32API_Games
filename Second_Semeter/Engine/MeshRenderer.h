#pragma once
#include "Component.h"

class Mesh;
class Material;

class MeshRenderer : public Component
{
public:
	MeshRenderer();
	virtual ~MeshRenderer();

public:
	void SetMesh(shared_ptr<Mesh> mesh) { m_mesh = mesh; }
	void SetMaterial(shared_ptr<Material> material, uint32 idx = 0);
	
	shared_ptr<Material> GetMaterial(uint32 idx = 0) { return m_materials[idx]; }

public:
	void Update();
	void Render();

private:
	shared_ptr<Mesh> m_mesh;
	vector<shared_ptr<Material>> m_materials;
};

