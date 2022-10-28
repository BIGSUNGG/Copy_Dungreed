#include "framework.h"
#include "Bullet.h"

Bullet::Bullet(int level, int num)
	: Ect(level,num)
{
	_ectType = Ect::BULLET;
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
			// TODO : �Ű����� ����� �� �� �־��ֱ�
			bool attackSuccess = _weapon.lock()->GiveDamage(creature);
			if(attackSuccess)
			{
				DestroyEvent();
				return;
			}
		}
	}
}

void Bullet::SetDirection(const Vector2& direction)
{
	_direction = direction;
	_direction.Normalize();
}

void Bullet::DestroyEvent()
{
	_isActive = false;

	if (_destroyEffect)
	{
		shared_ptr<Effect> effect = _destroyEffect();
		effect->GetObjectTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetWorldPos();
		effect->GetObjectTexture()->GetTransform()->GetAngle() = _texture->GetTransform()->GetAngle();

		Vector2 direction = _direction;
		effect->GetAnimation()->SetBeforeChangeFunc([=](shared_ptr<Quad> quad) {quad->GetTransform()->GetPos() -= (direction * quad->GetHalfSize().y); });
		effect->GetAnimation()->SetAfterChangeFunc([=](shared_ptr<Quad> quad) {quad->GetTransform()->GetPos() += (direction * quad->GetHalfSize().y); });

		GAME->AddEffect(effect);
	}
}
