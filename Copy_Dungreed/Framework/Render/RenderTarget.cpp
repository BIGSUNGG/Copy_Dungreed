#include "framework.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget(float width, float height)
{
	{
		D3D11_TEXTURE2D_DESC desc = {};
		desc.Width = (UINT)width;
		desc.Height = (UINT)height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;

		DEVICE->CreateTexture2D(&desc, nullptr, _rtvTexture.GetAddressOf());
	}

	{ // Create SRV
		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = 1;

		DEVICE->CreateShaderResourceView(_rtvTexture.Get(), &desc, _srv.GetAddressOf());
	}

	{ // Create RTV
		D3D11_RENDER_TARGET_VIEW_DESC desc = {};
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

		DEVICE->CreateRenderTargetView(_rtvTexture.Get(), &desc, _rtv.GetAddressOf());
	}
}

RenderTarget::~RenderTarget()
{
}

void RenderTarget::Set()
{
	DEVICE_CONTEXT->OMSetRenderTargets(1, _rtv.GetAddressOf(), nullptr);

	DEVICE_CONTEXT->ClearRenderTargetView(_rtv.Get(), _color);
}

void RenderTarget::SetColor(float* color)
{
	for (int i = 0; i < 4; i++)
	{
		_color[i] = color[i];
	}
}
