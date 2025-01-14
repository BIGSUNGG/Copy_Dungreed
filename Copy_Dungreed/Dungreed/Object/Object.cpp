#include "framework.h"
#include "Object.h"

Object::Object(int level, int num)
	: _level(level)
	, _num(num)
{
	_componentCollector = make_shared<ComponentCollector>(this);
	_buffer = make_shared<ObjectBuffer>();
}

void Object::Update()
{
	if (_anim != nullptr)
		_anim->Update();

	_componentCollector->Update();

	_texture->Update();
	_collider->Update();
}

void Object::PreRender()
{
}

void Object::Render()
{
	if (_render || GAME->GetPlaying() == false)
	{
		_buffer->SetPSBuffer(0);
		_texture->Render();
	}
}

void Object::PostRender()
{
	if (_collider == nullptr)
		return;

	_collider->Render();
}

void Object::ImGuiRender()
{
}

void Object::ReverseTexture()
{
	_texture->ReverseToX();
	SWITCH_BOOL(_reverseTexture);
}

void Object::SetSpawnPos(Vector2 pos)
{
	_spawnPos = pos;
	_texture->GetTransform()->GetPos() = pos;
}

void Object::SetOwnerMap(shared_ptr<StageMap> map)
{
	_ownerMap = map;
}

void Object::SetCollider(shared_ptr<RectCollider> collider)
{
	if (collider == nullptr)
		_collider = make_shared<RectCollider>(_texture->GetHalfSize());
	else
		_collider = collider;

	_collider->SetParent(_texture->GetTransform());
}

void Object::CreateAnimation()
{
	_anim = make_shared<Animation>();
}

void Object::SetTexture(shared_ptr<Quad> texture)
{
	_texture = texture;
	_texture->SetPS(L"Shader/ObjectShader/ObjectPixelShader.hlsl");
	SetCollider();
}
