#include "framework.h"
#include "Bullet.h"

Bullet::Bullet(int level, int num)
	: Etc(level,num)
{
	_etcType = Etc::BULLET;
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

	if (_anim != nullptr)
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
		if (_attacked[enemy] == true)
			continue;

		auto weapon = _weapon.lock();
		if (enemy == weapon->GetOwner())
			continue;

		shared_ptr<Creature> creature = dynamic_pointer_cast<Creature>(enemy);
		bool attackSuccess = weapon->GiveDamage(weapon->GetRandomDamage(), creature);
		if (attackSuccess)
		{
			--_hitCount;
			_attacked[enemy] = true;
			if (_hitCount <= 0)
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

	if (_destroyEffect == nullptr)
		return;

	shared_ptr<Effect> effect = _destroyEffect();
	effect->GetObjectTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetWorldPos();
	effect->GetObjectTexture()->GetTransform()->GetAngle() = _texture->GetTransform()->GetAngle();

	Vector2 direction = _direction;
	effect->GetAnimation()->SetBeforeChangeFunc([=](pair<int, int> pair) {effect->GetObjectTexture()->GetTransform()->GetPos() -= (direction * effect->GetObjectTexture()->GetHalfSize().y); });
	effect->GetAnimation()->SetAfterChangeFunc([=](pair<int, int> pair) {effect->GetObjectTexture()->GetTransform()->GetPos() += (direction * effect->GetObjectTexture()->GetHalfSize().y); });

	GAME->AddEffect(effect);

}
