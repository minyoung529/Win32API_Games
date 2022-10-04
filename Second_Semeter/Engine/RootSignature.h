#pragma once

class RootSignature
{
public:
	void Init(ComPtr<ID3D12Device> device);

	ComPtr<ID3D12RootSignature> GetSignature() { return m_signature; }

private:
	ComPtr<ID3D12RootSignature> m_signature;
};

