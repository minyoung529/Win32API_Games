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
	void SetMesh(shared_ptr<Mesh> mesh) { m_mesh = mesh; };
	void SetMaterial(shared_ptr<Material> material) { m_material = material; };

	shared_ptr<Mesh> GetMesh() { return m_mesh; }
	shared_ptr<Material> GetMaterial(){ return m_material; };

public:
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Mesh> m_mesh;
	shared_ptr<Material> m_material;
};

