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

public:
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

class ObjectBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int selected = 0;
		float value1 = 0;
		float value2 = 0;
		float value3 = 0;
	}_data;

	ObjectBuffer()
		: ConstantBuffer(&_data, sizeof(Data))
	{
	}
};