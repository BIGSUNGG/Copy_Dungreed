#pragma once
class Device
{
private:
	Device(HWND hWnd);
	~Device();

public:
	static void Create(HWND hWnd)
	{
		if (_instance == nullptr)
			_instance = new  Device(hWnd);
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Device* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();

	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() { return _device; }
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }
	Microsoft::WRL::ComPtr< IDXGISwapChain> GetSwapChain() { return _swapChain; }

	void Clear();
	void Present();

private:
	static Device* _instance;

	HWND _hWnd;

	Microsoft::WRL::ComPtr<ID3D11Device>			_device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>		_deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain>			_swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	_renderTargetView;
};