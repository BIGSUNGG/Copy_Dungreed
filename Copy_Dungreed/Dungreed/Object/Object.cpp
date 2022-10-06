#include "framework.h"
#include "Object.h"

Object::Object(int level, int num)
	: _level(level)
	, _num(num)
{
	_buffer = make_shared<ObjectBuffer>();
}

void Object::Update()
{
	if (_anim != nullptr && _playingAnim)
		_anim->Update();

	_texture->Update();
	_collider->Update();
}

void Object::PreRender()
{
}

void Object::Render()
{
	if (_render || GAME->GetObjectUpdate() == false)
	{
		_buffer->SetPSBuffer(0);
		_texture->Render();
	}
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

void Object::SetSpawnPos(Vector2 pos)
{
	_spawnPos = pos;
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
	_playingAnim = true;
}

void Object::SetTexture(shared_ptr<Quad> texture)
{
	_texture = texture;
	_texture->SetPS(L"Shader/ObjectShader/ObjectPixelShader.hlsl");
	SetCollider();
}
