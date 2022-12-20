#pragma once

// std::byte ������� ����.
#define _HAS_STD_BYTE 0

// ���� include 
#include <windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include <fstream>


// directX include
#include "d3dx12.h"
#include "SimpleMath.h"
#include <d3d12.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;

#include <DirectXTex.h>
#include <DirectXTex.inl>

#include "FBX/fbxsdk.h"

// ���� lib
#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex_Debug.lib")
#else
#pragma comment(lib, "DirectXTex.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "FBX\\debug\\libfbxsdk-md.lib")
#pragma comment(lib, "FBX\\debug\\libxml2-md.lib")
#pragma comment(lib, "FBX\\debug\\zlib-md.lib")

#else
#pragma comment(lib, "FBX\\release\\libfbxsdk-md.lib")
#pragma comment(lib, "FBX\\release\\libxml2-md.lib")
#pragma comment(lib, "FBX\\release\\zlib-md.lib")
#endif

// ���� typedef
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using Vec2 = DirectX::SimpleMath::Vector2;
using Vec3 = DirectX::SimpleMath::Vector3;
using Vec4 = DirectX::SimpleMath::Vector4;
using Matrix = DirectX::SimpleMath::Matrix;

// ���� struct
struct WindowInfo
{
	HWND	hwnd;		// ��� ������
	int32	width;		// �ʺ�
	int32	height;		// ����
	bool	windowed;	// â��� or ��üȭ��
};

enum class CBV_REGISTER : uint8
{
	b0,
	b1,
	b2,
	b3,
	b4,

	END
};

enum class SRV_REGISTER : uint8
{
	t0 = static_cast<uint8>(CBV_REGISTER::END),
	t1,
	t2,
	t3,
	t4,

	END
};


enum
{
	SWAP_CHAIN_BUFFER_COUNT = 2,
	CBV_VIEW_REGISTER_COUNT = 1, // b0
	CBV_REGISTER_COUNT = static_cast<uint8>(CBV_REGISTER::END) - CBV_VIEW_REGISTER_COUNT,
	SRV_REGISTER_COUNT = static_cast<uint8>(SRV_REGISTER::END) - CBV_REGISTER_COUNT ,
	REGISTER_COUNT = CBV_REGISTER_COUNT + SRV_REGISTER_COUNT,
};

struct Vertex
{
	Vertex() {}
	Vertex(Vec3 p, Vec2 u, Vec3 n, Vec3 t) 
		: pos(p), uv(u), normal(n), tangent(t)
	{
	}

	Vec3 pos;
	Vec2 uv;
	Vec3 normal;
	Vec3 tangent;
};

struct TransformParams
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProjection;
	Matrix matWV;
	Matrix matWVP;
};

// �̱��� ������
#define DECLARE_SINGLE(type)		\
private:							\
	type() {}						\
	~type() {}						\
public:								\
	static type* GetInstance()		\
	{								\
		static type instance;		\
		return &instance;			\
	}								\

#define GET_SINGLE(type)			type::GetInstance()


#define DEVICE				g_Engine->GetDevice()->GetDevice()
#define CMD_LIST			g_Engine->GetCmdQueue()->GetCmdList()
#define RESOURCE_CMD_LIST	g_Engine->GetCmdQueue()->GetResourceCmdList()
#define ROOT_SIGNATURE		g_Engine->GetRootSignature()->GetSignature()

#define INPUT				g_Engine->GetInput()
#define DELTA_TIME			g_Engine->GetTimer()->GetDeltaTime()

#define CONST_BUFFER(type)	g_Engine->GetConstantBuffer(type)

extern unique_ptr<class Engine> g_Engine;

// Utils
wstring s2ws(const string& s);
string ws2s(const wstring& s);