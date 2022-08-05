#pragma once
class Quad
{
public:
	Quad(wstring file, wstring vs = L"Shader/TextureVertexShader.hlsl", wstring ps = L"Shader/TexturePixelShader.hlsl");
	~Quad();

	virtual void Update();
	virtual void Render();

	virtual void CreateVertices();
	virtual void SetTexture(wstring file);
	virtual void SetVS(wstring vs);
	virtual void SetPS(wstring ps);

	shared_ptr<Transform> GetTransform() { return _transform; }
	const Vector2& GetSize() { return _size; }
	Vector2 GetHalfSize() { return _size * 0.5f; }

	float Top()		{ return _transform->GetWorldPos().y + (GetHalfSize().y * _transform->GetWorldScale().y); }
	float Bottom()	{ return _transform->GetWorldPos().y - (GetHalfSize().y * _transform->GetWorldScale().y); }
	float Right()	{ return _transform->GetWorldPos().x + (GetHalfSize().x * _transform->GetWorldScale().x); }
	float Left()	{ return _transform->GetWorldPos().x - (GetHalfSize().x * _transform->GetWorldScale().x); }
	
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

