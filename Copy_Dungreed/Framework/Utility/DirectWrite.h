#pragma once

using namespace Microsoft::WRL;

struct FontBrushDesc
{
	XMFLOAT4 _color;
	ComPtr<ID2D1SolidColorBrush> _brush;

	bool operator==(const FontBrushDesc& value)
	{
		return _color.x == value._color.x && _color.y == value._color.y &&
			_color.z == value._color.z && _color.w == value._color.w;
	}
};

struct FontTextDesc
{
	wstring _fontPath;
	float _fontSize;

	DWRITE_FONT_WEIGHT _weight;
	DWRITE_FONT_STYLE _style;
	DWRITE_FONT_STRETCH _stretch;

	ComPtr<IDWriteTextFormat> _format;

	bool operator==(const FontTextDesc& value)
	{
		bool result = true;

		result &= _fontPath == value._fontPath;
		result &= _fontSize == value._fontSize;
		result &= _weight == value._weight;
		result &= _style == value._style;
		result &= _stretch == value._stretch;
		
		return result;
	}
};

class DirectWrite
{
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new DirectWrite();
	}
	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}
	static DirectWrite* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
	}

	ComPtr<ID2D1DeviceContext> GetDC() { return _deviceContext; }

	void RenderText(wstring text, RECT rect, float size = 20.0f, wstring fontPath = L"DungGeunMo",
		XMFLOAT4 color = { 1,1,1,1 }
		, DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL
		, DWRITE_FONT_STYLE style = DWRITE_FONT_STYLE_NORMAL
		, DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL);

private:
	DirectWrite();
	~DirectWrite();

	static DirectWrite* _instance;

	ComPtr<ID2D1Factory1> _factory;
	ComPtr<IDWriteFactory> _writeFactory;

	ComPtr<ID2D1Device> _device;
	ComPtr<ID2D1DeviceContext> _deviceContext;

	ComPtr<ID2D1Bitmap1> _targetBitmap;

	vector<FontBrushDesc> _fontBrushes;
	vector<FontTextDesc> _fontTexts;
};

