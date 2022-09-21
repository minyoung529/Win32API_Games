#include "pch.h"
#include "RootSignature.h"

void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	// 셰이더에게 상수 버퍼를 알리기 위한 코드
	// 상수 버퍼 하나 만들 것!
	CD3DX12_ROOT_PARAMETER param[1];
	// 0번 -> b0에 바인딩 -> cbv(상수 버퍼 뷰가 됨)
	param[0].InitAsConstantBufferView(0);

	// param의 길이, param을 넘겨줌
	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(_countof(param), param);

	// 정점에 정보만 주겠다
	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<ID3DBlob> blobSignature;
	ComPtr<ID3DBlob> blobError;

	// 루트 시그니쳐 초기화
	::D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);

	// 생성
	device->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&signature));
}