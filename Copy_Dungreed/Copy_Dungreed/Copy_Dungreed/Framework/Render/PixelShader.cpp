#include "framework.h"
#include "PixelShader.h"

PixelShader::PixelShader(wstring file)
{
	CreatePixelblob(file);
	CreatePixelShader();
}

PixelShader::~PixelShader()
{
}

void PixelShader::CreatePixelblob(wstring file)
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	D3DCompileFromFile(file.data(), nullptr, nullptr, "PS", "ps_5_0", flags, 0,
		_blob.GetAddressOf(), nullptr);
}

void PixelShader::CreatePixelShader()
{
	DEVICE->CreatePixelShader(_blob->GetBufferPointer(), _blob->GetBufferSize(), nullptr,
		_pixelShader.GetAddressOf());
}

void PixelShader::Set()
{
	DEVICE_CONTEXT->PSSetShader(_pixelShader.Get(), nullptr, 0);
}
