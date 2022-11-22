#include "pch.h"
#include "Resources.h"

/// <summary>
/// ť�� �׸���
/// </summary>
shared_ptr<Mesh> Resources::LoadCubeMesh()
{
	shared_ptr<Mesh> findMesh = Get<Mesh>(L"Cube");

	if (findMesh)
		return findMesh;

	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;

	vector<Vertex> vec(24);

	// �ո�
	vec[0] = Vertex(Vec3(-w2, -h2, -d2), Vec2(0.0f, 1.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f));
	vec[1] = Vertex(Vec3(-w2, +h2, -d2), Vec2(0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f));
	vec[2] = Vertex(Vec3(+w2, +h2, -d2), Vec2(1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f));
	vec[3] = Vertex(Vec3(+w2, -h2, -d2), Vec2(1.0f, 1.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f));

	// �޸�
	vec[4] = Vertex(Vec3(-w2, -h2, +d2), Vec2(1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f));
	vec[5] = Vertex(Vec3(+w2, -h2, +d2), Vec2(0.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f));
	vec[6] = Vertex(Vec3(+w2, +h2, +d2), Vec2(0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f));
	vec[7] = Vertex(Vec3(-w2, +h2, +d2), Vec2(1.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f));

	// ����
	vec[8] = Vertex(Vec3(-w2, +h2, -d2), Vec2(0.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	vec[9] = Vertex(Vec3(-w2, +h2, +d2), Vec2(0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	vec[10] = Vertex(Vec3(+w2, +h2, +d2), Vec2(1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	vec[11] = Vertex(Vec3(+w2, +h2, -d2), Vec2(1.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	// �Ʒ���
	vec[12] = Vertex(Vec3(-w2, -h2, -d2), Vec2(1.0f, 1.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
	vec[13] = Vertex(Vec3(+w2, -h2, -d2), Vec2(0.0f, 1.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
	vec[14] = Vertex(Vec3(+w2, -h2, +d2), Vec2(0.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
	vec[15] = Vertex(Vec3(-w2, -h2, +d2), Vec2(1.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
	// ���ʸ�
	vec[16] = Vertex(Vec3(-w2, -h2, +d2), Vec2(0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f));
	vec[17] = Vertex(Vec3(-w2, +h2, +d2), Vec2(0.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f));
	vec[18] = Vertex(Vec3(-w2, +h2, -d2), Vec2(1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f));
	vec[19] = Vertex(Vec3(-w2, -h2, -d2), Vec2(1.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f));
	// �����ʸ�
	vec[20] = Vertex(Vec3(+w2, -h2, -d2), Vec2(0.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
	vec[21] = Vertex(Vec3(+w2, +h2, -d2), Vec2(0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
	vec[22] = Vertex(Vec3(+w2, +h2, +d2), Vec2(1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
	vec[23] = Vertex(Vec3(+w2, -h2, +d2), Vec2(1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));

	vector<uint32> idx(36);

	// �ո�
	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;
	// �޸�
	idx[6] = 4; idx[7] = 5; idx[8] = 6;
	idx[9] = 4; idx[10] = 6; idx[11] = 7;
	// ����
	idx[12] = 8; idx[13] = 9; idx[14] = 10;
	idx[15] = 8; idx[16] = 10; idx[17] = 11;
	// �Ʒ���
	idx[18] = 12; idx[19] = 13; idx[20] = 14;
	idx[21] = 12; idx[22] = 14; idx[23] = 15;
	// ���ʸ�
	idx[24] = 16; idx[25] = 17; idx[26] = 18;
	idx[27] = 16; idx[28] = 18; idx[29] = 19;
	// �����ʸ�
	idx[30] = 20; idx[31] = 21; idx[32] = 22;
	idx[33] = 20; idx[34] = 22; idx[35] = 23;

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh->Init(vec, idx);
	Add(L"Cube", mesh);

	return mesh;
}

shared_ptr<Mesh> Resources::LoadSphereMesh()
{
	shared_ptr<Mesh> findMesh = Get<Mesh>(L"Sphere");

	if (findMesh)
		return findMesh;

	float radius = 0.5f;	// ���� ������
	uint32 stackCount = 20;		// ������ �������� count
	uint32 sliceCount = 20; // ������ �������� count

	vector<Vertex> vec;

	// �ϱ� (0, 0.5, 0)
	Vertex v;
	v.pos = Vec3(0.f, radius, 0.f);
	v.uv = Vec2(0.5f, 0.f);
	v.normal = v.pos;
	v.normal.Normalize();
	v.tangent = Vec3(1.f, 0.f, 1.f);

	vec.push_back(v);

	// ����, �� ���
	float stackAngle = XM_PI / stackCount;
	float sliceAngle = XM_2PI / sliceCount;

	float deltaU = 1.0f / static_cast<float>(stackCount);
	float deltaV = 1.0f / static_cast<float>(sliceCount);

	for (uint32 y = 1; y <= stackCount - 1; ++y)
	{
		float phi = y * stackAngle;

		for (uint32 x = 0; x <= sliceCount; ++x)
		{
			float theta = x * sliceAngle;

			v.pos.x = radius * sinf(phi) * cosf(theta);
			v.pos.y = radius * cosf(phi);
			v.pos.z = radius * sinf(phi) * sinf(theta);

			v.uv = Vec2(deltaU * x, deltaV * y);
			v.normal = v.pos;
			v.normal.Normalize();

			v.tangent.x = -radius * sinf(phi) * cosf(theta);
			v.tangent.y = 0.f;
			v.tangent.z = -radius * sinf(phi) * sinf(theta);
			v.tangent.Normalize();

			vec.push_back(v);
		}
	}

	// ���� (0, -0.5, 0)
	v.pos = Vec3(0.f, -radius, 0.f);
	v.uv = Vec2(0.5f, 1.f);
	v.normal = v.pos; v.normal.Normalize();
	v.tangent = Vec3(1.f, 0.f, 0.f);
	vec.push_back(v);

	vector<uint32> idxes;

	// �ϱ� index
	for (uint32 i = 0; i <= sliceCount; ++i)
	{
		//[0]
		// |   \
		//[i+1][i+2]

		idxes.push_back(0);
		idxes.push_back(i + 2);
		idxes.push_back(i + 1);
	}

	// ���� index
	uint32 ringVertexCount = sliceCount + 1; // �� �ٿ� �����ؾ��ϴ� ����

	for (uint32 y = 0; y < stackCount - 2; ++y)
	{
		for (uint32 x = 0; x < sliceCount; ++x)
		{
			// +1 => �ϱ�

			// [y,x]1 - [y,x+1]2
			// |	   /
			// [y+1, x]3
			idxes.push_back(1 + y * ringVertexCount + (x));
			idxes.push_back(1 + y * ringVertexCount + (x + 1));
			idxes.push_back(1 + (y + 1) * ringVertexCount + (x));

			//			  [y, x+1]2
			//          /       |  
			// [y+1, x]1 - [y+1, x+1]3

			idxes.push_back(1 + (y + 1) * ringVertexCount + (x));
			idxes.push_back(1 + y * ringVertexCount + (x + 1));
			idxes.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
		}
	}

	uint32 bottomIndex = static_cast<uint32>(vec.size()) - 1;
	uint32 lastRingStartIndex = bottomIndex - ringVertexCount;

	for (uint32 i = 0; i < sliceCount; i++)
	{
		// [last+i] - [last+i+1]
		// |        / 
		// [bottom]

		idxes.push_back(bottomIndex);
		idxes.push_back(lastRingStartIndex + i);
		idxes.push_back(lastRingStartIndex + i + 1);
	}

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh->Init(vec, idxes);
	Add(L"Sphere", mesh);

	return mesh;
}

shared_ptr<Mesh> Resources::LoadPlaneMesh(float width, float depth, uint32 m, uint32 n)
{
	shared_ptr<Mesh> findMesh = Get<Mesh>(L"Plane");

	if (findMesh)
		return findMesh;

	uint32 vertexCount = m * n;
	uint32 faceCount = (m - 1) * (n - 1) * 2;

	float halfWidth = 0.5f * width;
	float halfDepth = 0.5f * depth;

	float dx = width / (n - 1);
	float dz = depth / (m - 1);

	float du = 1.0f / (n - 1);
	float dv = 1.0f / (m - 1);

	vector<Vertex> vec(vertexCount);

	for (uint32 z = 0; z < m; ++z)
	{
		float posZ = halfDepth - z * dz;

		for (uint32 x = 0; x < n; ++x)
		{
			float posX = -halfWidth + x * dx;
			int index = z * n + x;

			vec[index].pos = Vec3(posX, 0.f, posZ);
			vec[index].normal = Vec3::Up;
			vec[index].tangent = Vec3::Right;
			vec[index].uv = Vec2(du * x, dv * z);
		}
	}

	vector<uint32> idx(faceCount * 3);
	uint32 k = 0;

	for (int i = 0; i < m - 1; ++i)
	{
		for (int j = 0; j < n - 1; ++j)
		{
			idx[k] = i * n + j;					// 1
			idx[k + 1] = i * n + j + 1;			// 2
			idx[k + 2] = (i + 1) * n + j;		// 3

			idx[k + 3] = (i + 1) * n + j;		// 3
			idx[k + 4] = i * n + j + 1;			// 2
			idx[k + 5] = (i + 1) * n + j + 1;	// 4

			k += 6;
		}
	}

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh->Init(vec, idx);
	Add(L"Plane", mesh);

	return mesh;
}

shared_ptr<Mesh> Resources::LoadMeshFile(const wstring& path, const wstring& name)
{
	shared_ptr<Mesh> findMesh = Get<Mesh>(name);

	if (findMesh)
		return findMesh;

	ifstream fin(path.c_str());

	if (!fin)
	{
		wstring errorStr = path + L" not found.";
		MessageBox(0, errorStr.c_str(), 0, 0);
		return nullptr;
	}

	uint32 vertexCount = 0;
	uint32 tCount = 0;
	string ignore;

	fin >> ignore >> vertexCount;
	fin >> ignore >> tCount;
	fin >> ignore >> ignore >> ignore >> ignore;

	float du = 1.0f / (vertexCount - 1);
	float dv = 1.0f / (tCount - 1);

	vector<Vertex> vec(vertexCount);

	for (uint32 i = 0; i < vertexCount; i++)
	{
		fin >> vec[i].pos.x >> vec[i].pos.y >> vec[i].pos.z;
		fin >> vec[i].normal.x >> vec[i].normal.y >> vec[i].normal.z;
	}

	fin >> ignore >> ignore >> ignore;

	vector<uint32> tVec(tCount * 3);

	for (uint32 i = 0; i < tCount; i++)
	{
		fin >> tVec[i * 3] >> tVec[i * 3 + 1] >> tVec[i * 3 + 2];
	}

	fin.close();

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh->Init(vec, tVec);
	Add(name, mesh);

	return mesh;
}