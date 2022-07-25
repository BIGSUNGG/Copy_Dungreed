#pragma once

inline void IASetPT(D3D_PRIMITIVE_TOPOLOGY type = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	DEVICE_CONTEXT->IASetPrimitiveTopology(type);
}

class MatrixBuffer : public ConstantBuffer
{
	struct Data
	{
		XMMATRIX _matrix;
	};
public:
	MatrixBuffer()
	: ConstantBuffer(&_data, sizeof(Data))
	{
		_data._matrix = XMMatrixIdentity();
	}

	void Set(XMMATRIX value)
	{
		_data._matrix = XMMatrixTranspose(value);
	}

private:
	Data _data;
};

class ColorBuffer : public ConstantBuffer
{
	struct Data
	{
		XMFLOAT4 _color;
	};
public:
	ColorBuffer()
		: ConstantBuffer(&_data, sizeof(Data))
	{
		_data._color = { 1,1,1,1 };
	}

	void SetColor(const XMFLOAT4& color)
	{
		_data._color = color;
	}

private:
	Data _data;
};

class FrameBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT2 _maxFrame;
		XMFLOAT2 _curFrame;
	}_data;

	FrameBuffer()
	: ConstantBuffer(&_data, sizeof(Data))
	{
		_data._maxFrame = { 1,1 };
		_data._curFrame = { 1,1 };
	}
};

class ActionBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		// 16바이트씩 끊어서 읽는다.. => 16바이트의 정수배로 정보를 줘야함.
		Vector2 _startPos;
		Vector2 _maxSize;
		Vector2 _size;
		Vector2 padding;
	}_data;
	
	ActionBuffer()
	: ConstantBuffer(&_data, sizeof(Data))
	{
		_data._startPos = { 0,0 };
		_data._maxSize = { 0,0 };
		_data._size = { 0,0 };
		_data.padding = { 0,0 };
	}
};

class FilterBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int selected = 0;
		int value1 = 0;
		int value2 = 0;
		int value3 = 0;
	}_data;

	FilterBuffer()
		: ConstantBuffer(&_data, sizeof(Data))
	{
	}
};

class ImageSizeBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT2 size = { 0.0f,0.0f };
		XMFLOAT2 padding = { 0.0f,0.0f };
	}_data;

	ImageSizeBuffer()
		: ConstantBuffer(&_data, sizeof(Data))
	{
	}
};

class ButtonBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int _state = 0;
		float _hover = 0.0f;
		float _click = 0.0f;
		int padding;

	}_data;

	ButtonBuffer()
		: ConstantBuffer(&_data, sizeof(Data))
	{
	}
};