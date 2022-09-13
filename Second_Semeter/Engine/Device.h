#pragma once

// �ٸ� �������̽����� �����ϱ� ���� Ŭ����

// COM (Component Object Model)

class Device
{
public:
	void Init();
	ComPtr<IDXGIFactory> GetDXGI() { return dxgi; }
	ComPtr<ID3D12Device> GetDevice() { return device; }

private:
	// COMPtr == smatr ptr
	ComPtr<ID3D12Debug>		debugController;
	ComPtr<IDXGIFactory>	dxgi;			// ȭ�� ���� ��ɵ�
	ComPtr<ID3D12Device>	device;			// ������ �����ؾ��ϴ� �׷��� ī�� ��ġ (���� ��ü ����)
};