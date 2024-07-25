#pragma once
class CircleCollider;

class RectCollider : public Collider
{
public:
	struct ObbDesc
	{
		Vector2 _position;
		Vector2 _direction[2]; // 가로 세로
		float _length[2]; // 가로 세로
	};

	RectCollider(const Vector2& halfSize);
	virtual ~RectCollider();

	void CreateVertices();

	virtual void Update() override;
	virtual void Render() override;

	void SetHalfSize(const Vector2& halfSize) { _halfSize = halfSize; }
	Vector2& GetHalfSize() { return _halfSize; }

	float Top() { return GetWorldPos().y + (_halfSize.y * _transform->GetWorldScale().y); }
	float Bottom() { return GetWorldPos().y - (_halfSize.y * _transform->GetWorldScale().y); }
	float Right() { return GetWorldPos().x + (_halfSize.x * _transform->GetWorldScale().x); }
	float Left() { return GetWorldPos().x - (_halfSize.x * _transform->GetWorldScale().x); }

	void SetTop(float pos) { _transform->GetPos().y = pos - (GetHalfSize().y * _transform->GetScale().y); }
	void SetBottom(float pos) { _transform->GetPos().y = pos + (GetHalfSize().y * _transform->GetScale().y); }
	void SetRight(float pos) { _transform->GetPos().x = pos - (GetHalfSize().x * _transform->GetScale().x); }
	void SetLeft(float pos) { _transform->GetPos().x = pos + (GetHalfSize().x * _transform->GetScale().x); }

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(shared_ptr<RectCollider> rect, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other, bool isObb = false) override;
	
	float SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2);

	bool IsOBB(shared_ptr<RectCollider> rect);
	bool IsAABB(shared_ptr<RectCollider> rect);

	bool IsOBB(shared_ptr<class CircleCollider> circle);
	bool IsAABB(shared_ptr<class CircleCollider> circle);

	ObbDesc GetOBB();

private:
	Vector2 _halfSize = { 0,0 };
};

