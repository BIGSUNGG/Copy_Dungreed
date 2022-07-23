#pragma once
class CircleCollider : public Collider
{
public:
	CircleCollider(const float& radius);
	virtual ~CircleCollider();

	void CreateVertices();

	virtual void Update() override;
	virtual void Render() override;

	float GetRadius() { return _radius * _transform->GetWorldScale().x; }

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<class RectCollider> rect, bool isObb = false) override;

private:
	float _radius = 0;
};

