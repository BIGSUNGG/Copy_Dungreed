#pragma once
class Quad
{
public:
	Quad(wstring file, wstring vs = L"Shader/TextureVertexShader.hlsl", wstring ps = L"Shader/TexturePixelShader.hlsl");
	~Quad();

	virtual void Update();
	virtual void Render();

	virtual void ReverseToX();
	virtual void ReverseToY();

	virtual void CreateVertices();
	virtual void SetTexture(wstring file);
	virtual void SetVS(wstring vs);
	virtual void SetPS(wstring ps);

	shared_ptr<Transform> GetTransform() { return _transform; }
	const Vector2& GetSize() { return _size; }
	Vector2 GetHalfSize() { return _size * 0.5f; }

	float Top()		{ return _transform->GetPos().y + (GetHalfSize().y * _transform->GetScale().y); }
	float Bottom()	{ return _transform->GetPos().y - (GetHalfSize().y * _transform->GetScale().y); }
	float Right()	{ return _transform->GetPos().x + (GetHalfSize().x * _transform->GetScale().x); }
	float Left()	{ return _transform->GetPos().x - (GetHalfSize().x * _transform->GetScale().x); }
	
	void SetTop		(float pos) { _transform->GetPos().y = pos - (GetHalfSize().y * _transform->GetScale().y); }
	void SetBottom	(float pos) { _transform->GetPos().y = pos + (GetHalfSize().y * _transform->GetScale().y); }
	void SetRight	(float pos) { _transform->GetPos().x = pos - (GetHalfSize().x * _transform->GetScale().x); }
	void SetLeft	(float pos) { _transform->GetPos().x = pos + (GetHalfSize().x * _transform->GetScale().x); }

protected:
	Quad();

	shared_ptr<Transform> _transform;

	// Mesh
	vector<VertexUV> _vertices;
	vector<UINT> _indices;
	shared_ptr<VertexBuffer>	_vertexBuffer;
	shared_ptr<IndexBuffer>		_indexBuffer;

	// Material
	// Texture
	shared_ptr<Texture> _texture;
	shared_ptr<VertexShader>	_vertexShader;
	shared_ptr<PixelShader>		_pixelShader;

	wstring _vs;
	wstring _ps;

	Vector2 _size;
};

