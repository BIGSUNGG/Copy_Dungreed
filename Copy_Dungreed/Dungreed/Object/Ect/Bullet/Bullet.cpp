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
	if (_weapon.lock() == nullptr)
	{
		DestroyEvent();
		return;
	}

	_runTime += DELTA_TIME;

	if (_runTime >= _runTimeMax)
		DestroyEvent();

	if (_anim != nullptr && _playingAnim)
		_anim->Update();

	_texture->GetTransform()->GetPos() += (_direction * (_speed * DELTA_TIME));

	Object::Update();

	Attack();
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
		if (enemy != _weapon.lock()->GetOwner())
		{
			shared_ptr<Creature> creature = dynamic_pointer_cast<Creature>(enemy);
			// TODO : 매개변수 제대로 된 값 넣어주기
			if (creature->Damaged(Status()))
			{
				DestroyEvent();
				return;
			}
		}
	}
}

void Bullet::DestroyEvent()
{
	_isActive = false;
}
