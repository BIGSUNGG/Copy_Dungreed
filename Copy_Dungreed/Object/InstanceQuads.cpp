#include "framework.h"
#include "InstanceQuads.h"

InstanceQuads::InstanceQuads(wstring file, int count)
{
	_quad = make_shared<Quad>(file, L"Shader/InstancingShader/InstancingVertexShader.hlsl", L"Shader/InstancingShader/InstancingPixelShader.hlsl");

	_instanceDataes.resize(count);

	for (auto& instanceData : _instanceDataes)
	{
		shared_ptr<Transform> temp = make_shared<Transform>();
		_transforms.emplace_back(temp);
		temp->UpdateWorld();

		instanceData = XMMatrixTranspose(temp->GetMatrix());
	}

	_instancingBuffer = make_shared<VertexBuffer>(_instanceDataes.data(), sizeof(XMMATRIX), _instanceDataes.size());
}

InstanceQuads::InstanceQuads(shared_ptr<Quad> quad, int count)
	: _quad(quad)
{
	_instanceDataes.resize(count);

	for (auto& instanceData : _instanceDataes)
	{
		shared_ptr<Transform> temp = make_shared<Transform>();
		_transforms.emplace_back(temp);
		temp->UpdateWorld();

		instanceData = XMMatrixTranspose(temp->GetMatrix());
	}

	_instancingBuffer = make_shared<VertexBuffer>(_instanceDataes.data(), sizeof(XMMATRIX), _instanceDataes.size());
}

void InstanceQuads::Update()
{
}

void InstanceQuads::Render()
{
	_instancingBuffer->IASetVertexBuffer(1);

	_quad->SetRender();

	DEVICE_CONTEXT->DrawIndexedInstanced(6, _instanceDataes.size() * _renderPercent, 0, 0, 0);
}

void InstanceQuads::ApplyChanges()
{
	_instanceDataes.clear();

	for (int i = 0; i < _transforms.size(); i++)
	{
		_transforms[i]->UpdateWorld();
		_instanceDataes.emplace_back(XMMatrixTranspose(_transforms[i]->GetMatrix()));
	}
	_instancingBuffer = make_shared<VertexBuffer>(_instanceDataes.data(), sizeof(XMMATRIX), _instanceDataes.size());
}
