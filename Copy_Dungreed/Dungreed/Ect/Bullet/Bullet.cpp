#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	_runTime += DELTA_TIME;

	if (_runTime >= _runTimeMax)
		DestroyEvent();

	if (_anim != nullptr && _playingAnim)
		_anim->Update();

	_texture->GetTransform()->GetPos() += (_direction * (_speed * DELTA_TIME));

	_texture->Update();
	_collider->Update();

	Attack();
}

void Bullet::Render()
{
	_texture->Render();
}

void Bullet::PostRender()
{
	_collider->Render();
}

void Bullet::ReverseTexture()
{
	_texture->ReverseToX();
}

void Bullet::Attack()
{
	vector<shared_ptr<Object>> _collisions = GAME->GetCollisions(_collider, Object::Object_Type::CREATURE);
	for (auto& enemy : _collisions)
	{
		if(enemy != _weapon.lock()->GetOwner())
		{
			shared_ptr<Creature> creature = dynamic_pointer_cast<Creature>(enemy);
			// TODO : 매개변수 제대로 된 값 넣어주기
			creature->Damaged(Status());
			DestroyEvent();
			return;
		}
	}
}

void Bullet::DestroyEvent()
{
	_isActive = false;
}

void Bullet::SetCollider()
{
	_collider = make_shared<RectCollider>(_texture->GetHalfSize());
	_collider->SetParent(_texture->GetTransform());
}

void Bullet::SetAnimation()
{
	_anim = make_shared<Animation>();
	_playingAnim = true;
}

void Bullet::SetTexture(shared_ptr<Quad> texture)
{
	_texture = texture;
	SetCollider();
}
