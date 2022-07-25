#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(const float& radius)
: _radius(radius)
{
	_type = Collider::Type::CIRCLE;
	_vertices.reserve(37);

	CreateVertices();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::CreateVertices()
{
	VertexPos v;

	float theta = 2 * PI / 36;

	for (int i = 0; i < 37; i++)
	{
		v.pos.x = cosf(theta * i) * _radius;
		v.pos.y = sinf(theta * i) * _radius;
		v.pos.z = 0;
		_vertices.push_back(v);
	}

	_vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexPos), _vertices.size());
	
	Collider::CreateData();
}

void CircleCollider::Update()
{
	Collider::Update();
}

void CircleCollider::Render()
{
	Collider::Render();
}

bool CircleCollider::IsCollision(const Vector2& pos)
{
	float distance = pos.Distance(GetWorldPos());
	float radius = GetRadius();

    return distance < radius;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other, bool isObb)
{
	Vector2 otherPos = other->GetWorldPos();
	Vector2 mine = GetWorldPos();

	Vector2 thisToOther = otherPos - mine;
	float radius = GetRadius();
	float radiusOther = other->GetRadius();

    return thisToOther.Length() < (radius + radiusOther);
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> rect, bool isObb)
{
	return rect->IsCollision(make_shared<CircleCollider>(*this), isObb);
}

