#pragma once

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

// directX include
#include "d3dx12.h"
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

// ���� lib
#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

// ���� typedef
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using Vec2 = XMFLOAT2;
using Vec3 = XMFLOAT3;
using Vec4 = XMFLOAT4;
using Matrix = XMMATRIX;

// ���� struct
struct WindowInfo
{
	HWND	hwnd;		// ��� ������
	int32	width;		// �ʺ�
	int32	height;		// ����
	bool	windowed;	// â��� or ��üȭ��
};

enum class CBV_REGISTER
{
	b0,
	b1,
	b2,
	b3,
	b4,

	END
};

enum
{
	SWAP_CHAIN_BUFFER_COUNT = 2,
	CBV_REGISTER_COUNT = CBV_REGISTER::END,
	REGISTER_COUNT = CBV_REGISTER::END
};

struct Vertex
{
	Vec3 pos;
	Vec4 color;
};

struct Transform
{
	Vec3 offset;
};

struct Color
{
	Vec4 offset;
};

#define DEVICE			g_Engine->GetDevice()->GetDevice()
#define CMD_LIST		g_Engine->GetCmdQueue()->GetCmdList()
#define ROOT_SIGNATURE	g_Engine->GetRootSignature()->GetSignature()

#define INPUT			g_Engine->GetInput()
#define DELTA_TIME		g_Engine->GetTimer()->GetDeltaTime()

extern unique_ptr<class Engine> g_Engine;