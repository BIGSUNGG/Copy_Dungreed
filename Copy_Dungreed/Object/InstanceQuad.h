#pragma once
class InstanceQuad
{
public:
	InstanceQuad(wstring file, int count);
	InstanceQuad(shared_ptr<Quad> quad, int count);

	virtual void Update();
	virtual void Render();

	shared_ptr<Quad> GetTexture() { return _quad; }
	vector<shared_ptr<Transform>>& GetTransforms() { return _transforms; }

	void SetRenderPercent(float percent) { _renderPercent = percent; }

	void ApplyChanges();
protected:
	float _renderPercent = 1;

	shared_ptr<Quad> _quad;
	vector<XMMATRIX> _instanceDataes;
	vector<shared_ptr<Transform>> _transforms;
	shared_ptr<VertexBuffer> _instancingBuffer;
};

