#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(const Vector2& halfSize)
: _halfSize(halfSize)
{
	_type = Collider::Type::RECT;
	_vertices.reserve(5);

	CreateVertices();
}

RectCollider::~RectCollider()
{
}

void RectCollider::CreateVertices()
{
	VertexPos v;
	// 왼쪽 위
	v.pos = { -_halfSize.x, _halfSize.y, 0 };
	_vertices.push_back(v);

	// 오른쪽 위
	v.pos = { _halfSize.x, _halfSize.y, 0 };
	_vertices.push_back(v);

	// 오른쪽 아래
	v.pos = { _halfSize.x, -_halfSize.y, 0 };
	_vertices.push_back(v);

	// 왼쪽 아래
	v.pos = { -_halfSize.x, -_halfSize.y, 0 };
	_vertices.push_back(v);

	// 왼쪽 위
	v.pos = { -_halfSize.x, _halfSize.y, 0 };
	_vertices.push_back(v);

	_vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexPos), _vertices.size());

	Collider::CreateData();
}

void RectCollider::Update()
{
	Collider::Update();
}

void RectCollider::Render()
{
	Collider::Render();
}

bool RectCollider::IsCollision(const Vector2& pos)
{
	if (pos.x < Left() || pos.x > Right())
		return false;
	if (pos.y > Top() || pos.y < Bottom())
		return false;
	return true;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> rect, bool isObb)
{
	if (isObb)
		return IsOBB(rect);
	else
		return IsAABB(rect);
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> circle, bool isObb)
{
	if (isObb)
		return IsOBB(circle);
	else
		return IsAABB(circle);
}

float RectCollider::SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2)
{
	float r1 = abs(separate.Dot(e1));
	float r2 = abs(separate.Dot(e2));

	return r1 + r2;
}

bool RectCollider::IsOBB(shared_ptr<RectCollider> rect)
{
	ObbDesc obbA = GetOBB();
	ObbDesc obbB = rect->GetOBB();

	Vector2 distance = obbA._position - obbB._position;

	// n : Nomal의 약자
	// e : edge의 약자
	Vector2 nea1 = obbA._direction[0];
	Vector2 ea1 = nea1 * obbA._length[0];
	Vector2 nea2 = obbA._direction[1];
	Vector2 ea2 = nea2 * obbA._length[1];

	Vector2 neb1 = obbB._direction[0];
	Vector2 eb1 = neb1 * obbB._length[0];
	Vector2 neb2 = obbB._direction[1];
	Vector2 eb2 = neb2 * obbB._length[1];

	// nea1 기준으로 직교
	float lengthA = ea1.Length();
	float lengthB = SeparateAxis(nea1, eb1, eb2);
	float length = abs(nea1.Dot(distance));
	if (length > lengthA + lengthB)
		return false;

	// nea2 기준으로 직교
	lengthA = ea2.Length();
	lengthB = SeparateAxis(nea2, eb1, eb2);
	length = abs(nea2.Dot(distance));
	if (length > lengthA + lengthB)
		return false;

	// neb1 기준으로 직교
	lengthA = SeparateAxis(neb1,ea1,ea2);
	lengthB = eb1.Length();
	length = abs(neb1.Dot(distance));
	if (length > lengthA + lengthB)
		return false;

	// neb2 기준으로 직교
	lengthA = SeparateAxis(neb2, ea1, ea2);
	lengthB = eb2.Length();
	length = abs(neb2.Dot(distance));
	if (length > lengthA + lengthB)
		return false;

	return true;
}

bool RectCollider::IsAABB(shared_ptr<RectCollider> rect)
{
	if (Right() < rect->Left())
		return false;
	if (Bottom() > rect->Top())
		return false;
	if (Left() > rect->Right())
		return false;
	if (Top() < rect->Bottom())
		return false;
	return true;
}

bool RectCollider::IsOBB(shared_ptr<CircleCollider> circle)
{
	ObbDesc obbA = GetOBB();

	Vector2 circlePos = circle->GetWorldPos();
	Vector2 distance = obbA._position - circle->GetWorldPos();

	Vector2 nea1 = obbA._direction[0];
	Vector2 ea1 = nea1 * obbA._length[0];
	Vector2 nea2 = obbA._direction[1];
	Vector2 ea2 = nea2 * obbA._length[1];

	float t = sqrtf(obbA._length[0] * obbA._length[0] + obbA._length[1] * obbA._length[1]) + circle->GetRadius();

	if (distance.Length() > t)
		return false;

	// Rect의 가로축 nea1 벡터로 투영
	float lengthA = ea1.Length();
	float lengthB = circle->GetRadius();
	float length = abs(distance.Dot(nea1));
	if (length > lengthA + lengthB)
		return false;
	
	// Rect의 세로축 nea2 벡터로 투영
	lengthA = ea2.Length();
	lengthB = circle->GetRadius();
	length = abs(distance.Dot(nea2));
	if (length > lengthA + lengthB)
		return false;

	return true;
}

bool RectCollider::IsAABB(shared_ptr<CircleCollider> circle)
{
	Vector2 circleCenter = circle->GetWorldPos();
	float left = Left();
	float top = Top();
	float right = Right();
	float bottom = Bottom();
	float radius = circle->GetRadius();

	if (left - radius < circleCenter.x && right + radius > circleCenter.x)
	{
		if (top + radius > circleCenter.y && bottom - radius < circleCenter.y )
			return true;
	}

	if (circle->IsCollision(Vector2(Right(), Top())))
		return true;
	if (circle->IsCollision(Vector2(Left(), Top())))
		return true;
	if (circle->IsCollision(Vector2(Right(), Bottom())))
		return true;
	if (circle->IsCollision(Vector2(Left(), Bottom())))
		return true;

	return false;
}

RectCollider::ObbDesc RectCollider::GetOBB()
{
	ObbDesc obbDesc;

	obbDesc._position = GetPos();

	obbDesc._length[0] = _halfSize.x * _transform->GetWorldScale().x;
	obbDesc._length[1] = _halfSize.y * _transform->GetWorldScale().y;

	XMFLOAT4X4 world;
	XMStoreFloat4x4(&world, (_transform->GetMatrix()));

	obbDesc._direction[0] = { world._11,world._12 };
	obbDesc._direction[1] = { world._21, world._22 };

	obbDesc._direction[0].Normalize();
	obbDesc._direction[1].Normalize();

	return obbDesc;
}
