#include "pch.h"
#include "RootSignature.h"

// ��Ʈ�ñ״�ó
// ��� ����
// Ŀ�ǵ� ť

void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	// ���̴����� ��� ���۸� �˸��� ���� �ڵ�
	// ��� ���� �ϳ� ���� ��!
	CD3DX12_ROOT_PARAMETER param[2];

	// 0�� -> b0�� ���ε� -> cbv(��� ���� �䰡 ��)
	param[0].InitAsConstantBufferView(0);
	param[1].InitAsConstantBufferView(1);

	// param�� ����, param�� �Ѱ���
	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(_countof(param), param);

	// ������ ������ �ְڴ�
	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<ID3DBlob> blobSignature;
	ComPtr<ID3DBlob> blobError;

	// ��Ʈ �ñ״��� �ʱ�ȭ
	::D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);

	// ����
	device->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&signature));
}