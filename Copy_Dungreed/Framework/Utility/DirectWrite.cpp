#include "framework.h"
#include "DirectWrite.h"

DirectWrite* DirectWrite::_instance = nullptr;

DirectWrite::DirectWrite()
{
	assert(SUCCEEDED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory), (IUnknown**)_writeFactory.GetAddressOf())));

	assert(SUCCEEDED(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, _factory.GetAddressOf())));

	ComPtr<IDXGIDevice> dxgiDevice;
	
	V(DEVICE->QueryInterface(dxgiDevice.GetAddressOf()));

	V(_factory->CreateDevice(dxgiDevice.Get(), _device.GetAddressOf()));

	V(_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
		_deviceContext.GetAddressOf()));

	ComPtr<IDXGISurface> dxgiSurface;
	V(Device::GetInstance()->GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)dxgiSurface.GetAddressOf()));

	D2D1_BITMAP_PROPERTIES1 bp;
	bp.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	bp.dpiX = 96;
	bp.dpiY = 96;
	bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext = nullptr;

	V(_deviceContext->CreateBitmapFromDxgiSurface(dxgiSurface.Get(), &bp, _targetBitmap.GetAddressOf()));

	_deviceContext->SetTarget(_targetBitmap.Get());
}

DirectWrite::~DirectWrite()
{
}

void DirectWrite::RenderText(wstring text, RECT rect, float size, wstring fontPath, XMFLOAT4 color, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch)
{
	GetDC()->BeginDraw();

	FontBrushDesc brushDesc;
	brushDesc._color = color;

	FontBrushDesc* findBrush = nullptr;
	for (auto& desc : _fontBrushes)
	{
		if (desc == brushDesc)
		{
			findBrush = &desc;
			break;
		}
	}

	if (findBrush == nullptr)
	{
		D2D1::ColorF colorF = D2D1::ColorF(color.x, color.y, color.z);
		V(_deviceContext->CreateSolidColorBrush(colorF, OUT brushDesc._brush.GetAddressOf()));

		_fontBrushes.emplace_back(brushDesc);
		findBrush = &brushDesc;
	}
	
	FontTextDesc fontDesc;
	fontDesc._fontPath = fontPath;
	fontDesc._fontSize = size;
	fontDesc._weight = weight;
	fontDesc._stretch = stretch;
	fontDesc._style = style;

	FontTextDesc* findText = nullptr;
	
	for (auto& desc : _fontTexts)
	{
		if (desc == fontDesc)
		{
			findText = &desc;
			break;
		}
	}

	if (findText == nullptr)
	{
		V(_writeFactory->CreateTextFormat(fontDesc._fontPath.c_str(), nullptr, fontDesc._weight, fontDesc._style,
			fontDesc._stretch, fontDesc._fontSize, L"ko", fontDesc._format.GetAddressOf()));

		_fontTexts.emplace_back(fontDesc);
		findText = &fontDesc;
	}

	D2D1_RECT_F rectF;
	rectF.left = (float)rect.left;
	rectF.right = (float)rect.right;
	rectF.top = (float)rect.top;
	rectF.bottom = (float)rect.bottom;

	_deviceContext->DrawTextW(text.c_str(), text.size(), findText->_format.Get(), &rectF, findBrush->_brush.Get());

	GetDC()->EndDraw();
}

