#include "framework.h"
#include "Device.h"

Device* Device::_instance = nullptr;

Device::Device(HWND hWnd)
    : _hWnd(hWnd)
{
    _hWnd = _hWnd;

    CreateDeviceAndSwapChain();
    CreateBackBuffer();
}

Device::~Device()
{
}

void Device::CreateDeviceAndSwapChain()
{
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };
    UINT featureSize = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = WIN_WIDTH;
    sd.BufferDesc.Height = WIN_HEIGHT;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    // RefreshRate = 디스플레이 모드 주사율 (Numerator / Denominator)
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = _hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;

    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        featureLevels,
        featureSize,
        D3D11_SDK_VERSION,
        &sd,
        _swapChain.GetAddressOf(),
        _device.GetAddressOf(),
        nullptr,
        _deviceContext.GetAddressOf()
    );
}

void Device::CreateBackBuffer()
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;

    _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
    _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());

    _deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);
}

void Device::Clear()
{
    FLOAT myColorR = 0.0f / 255.0f;
    FLOAT myColorG = 0.0f / 255.0f;
    FLOAT myColorB = 0.0f / 255.0f;
    FLOAT clearColor[4] = { myColorR, myColorG, myColorB, 1.0f };

    _deviceContext->ClearRenderTargetView(_renderTargetView.Get(), clearColor);
}

void Device::Present()
{
    _swapChain->Present(0, 0);
}
