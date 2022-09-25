#include "framework.h"
#include "InstanceQuads.h"

InstanceQuads::InstanceQuads(wstring file, int size)
{
	_quad = make_shared<Quad>(L"Resource/Ui/Nomal/HpBar_Gauge.png", L"Shader/InstancingShader/InstancingVertexShader.hlsl", L"Shader/InstancingShader/InstancingPixelShader.hlsl");

	_instanceDataes.resize(size);

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
	for (int i = 0; i < _instanceDataes.size(); i++)
	{
		_transforms[i]->UpdateWorld();
		_instanceDataes[i] = XMMatrixTranspose(_transforms[i]->GetMatrix());
	}
	_instancingBuffer = make_shared<VertexBuffer>(_instanceDataes.data(), sizeof(XMMATRIX), _instanceDataes.size());
}
