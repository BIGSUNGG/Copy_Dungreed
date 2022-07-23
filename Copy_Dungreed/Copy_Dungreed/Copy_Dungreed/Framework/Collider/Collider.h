#pragma once

class RectCollider;
class CircleCollider;

class Collider
{
protected:
	enum class Type
	{
		DEFAULT,
		CIRCLE,
		RECT
	};

public:
	Collider();
	virtual ~Collider();

	virtual void CreateData();

	virtual void Update();
	virtual void Render();

	Vector2& GetPos() { return _transform->GetPos(); }
	Vector2 GetWorldPos() { return _transform->GetWorldPos(); }
	float& GetAngle() { return _transform->GetAngle(); }
	shared_ptr<Transform> GetTransform() { return _transform; }

	void SetColorRed() { _colorBuffer->SetColor(RED); }
	void SetColorGreen() { _colorBuffer->SetColor(GREEN); }

	bool IsCollision(shared_ptr<Collider> col, bool isObb = false);

	virtual bool IsCollision(const Vector2& pos) abstract;
	virtual bool IsCollision(shared_ptr<CircleCollider> other, bool isObb = false) abstract;
	virtual bool IsCollision(shared_ptr<class RectCollider> rect, bool isObb = false) abstract;

	void SetParent(shared_ptr<Transform> parent) { _transform->SetParent(parent); }

protected:
	vector<VertexPos> _vertices;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<PixelShader> _pixelShader;
	shared_ptr<VertexShader> _vertexShader;

	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _parent;

	Type _type;
};

