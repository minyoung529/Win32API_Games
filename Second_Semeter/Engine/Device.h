#pragma once

// 다른 인터페이스들을 생성하기 위한 클래스

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
	ComPtr<IDXGIFactory>	dxgi;			// 화면 관련 기능들
	ComPtr<ID3D12Device>	device;			// 실제로 접근해야하는 그래픽 카드 장치 (각종 객체 생성)
};