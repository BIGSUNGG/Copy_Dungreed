#include "framework.h"
#include "Object.h"

Object::Object(int level, int num)
	: _level(level)
	, _num(num)
{
}

void Object::Update()
{
	if (_anim != nullptr)
		_anim->Update();

	_texture->Update();
	_collider->Update();
}

void Object::Render()
{
	_texture->Render();
}

void Object::PostRender()
{
	_collider->Render();
}

void Object::ImGuiRender()
{
}

void Object::ReverseTexture()
{
	_texture->ReverseToX();
	SwitchBool(_reversed);
}

void Object::SetOriginalPos(Vector2 pos)
{
	_texture->GetTransform()->GetPos() = pos;
}

void Object::SetCollider()
{
	_collider = make_shared<RectCollider>(_texture->GetHalfSize());
	_collider->SetParent(_texture->GetTransform());
}

void Object::SetAnimation()
{
	_anim = make_shared<Animation>();
}

void Object::SetTexture(shared_ptr<Quad> texture)
{
	_texture = texture;
	SetCollider();
}
