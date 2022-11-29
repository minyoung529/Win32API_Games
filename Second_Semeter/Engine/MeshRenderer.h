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
	void SetMaterial(shared_ptr<Material> material) { m_material = material; }

public:
	void Update();
	void Render();

private:
	shared_ptr<Mesh> m_mesh;
	shared_ptr<Material> m_material;
};

