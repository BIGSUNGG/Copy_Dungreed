#pragma once

class VertexBuffer
{
public:
	VertexBuffer(void* data, UINT stride, UINT count, UINT offset = 0);
	~VertexBuffer();
	
	void CreateBuffer(void* data);

	void IASetVertexBuffer(int slot);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> _vertexBuffer;

	UINT _stride = 0;
	UINT _count = 0;
	UINT _offset = 0;
};

