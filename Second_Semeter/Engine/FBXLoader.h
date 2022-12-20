#pragma once

struct FbxMaterialInfo
{
	Vec4			diffuse;
	Vec4			ambient;
	Vec4			specular;
	wstring			name;
	wstring			diffuseTexName;
	wstring			normalTexName;
	wstring			specularTexName;
};

struct FbxMeshInfo
{
	wstring						name;
	vector<Vertex>				vertices;
	vector<vector<uint32>>		indices;
	vector<FbxMaterialInfo>		materials;
};

class FBXLoader
{
public:
	FBXLoader();
	~FBXLoader();

public:
	void LoadFbx(const wstring& path);

	int32 GetMeshCount() { return static_cast<int32>(m_meshes.size()); }
	const FbxMeshInfo& GetMesh(int32 idx) { return m_meshes[idx]; }

private:
	void Import(const wstring& path);
	void ParseNode(FbxNode* root);
	void LoadMesh(FbxMesh* mesh);
	void LoadMaterial(FbxSurfaceMaterial* surfaceMaterial);

	void	GetNormal(FbxMesh* mesh, FbxMeshInfo* container, int32 idx, int32 vertexCounter);
	void	GetTangent(FbxMesh* mesh, FbxMeshInfo* container, int32 idx, int32 vertexCounter);
	void	GetUV(FbxMesh* mesh, FbxMeshInfo* container, int32 idx, int32 vertexCounter);
	Vec4	GetMaterialData(FbxSurfaceMaterial* surface, const char* materialName, const char* factorName);
	wstring	GetTextureRelativeName(FbxSurfaceMaterial* surface, const char* materialProperty);

public:
	void CreateTextures();
	void CreateMaterials();

private:
	FbxManager*				m_manager = nullptr;
	FbxScene*				m_scene = nullptr;
	FbxImporter*			m_importer = nullptr;
	wstring					m_resourceDirectory;

	vector<FbxMeshInfo>		m_meshes;
};