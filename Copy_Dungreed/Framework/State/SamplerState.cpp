#include "framework.h"
#include "SamplerState.h"

SamplerState::SamplerState()
{
    CreateSampler();
}

SamplerState::~SamplerState()
{
}

void SamplerState::CreateSampler()
{
    _desc = {};
    _desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    _desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    _desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    _desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    _desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    _desc.MinLOD = 0;
    _desc.MaxLOD = D3D11_FLOAT32_MAX;

    Changed();
}

void SamplerState::SetSamplerState(UINT slot)
{
    DEVICE_CONTEXT->PSSetSamplers(0, 1, _samplerState.GetAddressOf());
}

void SamplerState::Changed()
{
    if (_samplerState != nullptr)
        _samplerState->Release();

    DEVICE->CreateSamplerState(&_desc, _samplerState.GetAddressOf());
}
