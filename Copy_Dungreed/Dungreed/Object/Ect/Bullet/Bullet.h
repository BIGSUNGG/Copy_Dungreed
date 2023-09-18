#pragma once

class Item;

class Bullet : public Ect
{
public:
	Bullet(int level, int num);
	virtual ~Bullet();

	void Update();

	void ReverseTexture();
	virtual void Attack();

	void SetDirection(const Vector2& direction);
	void SetSpeed(float speed) { _speed = speed; }
	void SetHitCount(const float& count) { _hitCount = count; }
	void SetDestroyTime(const float& time) { _runTimeMax = time; }
	void SetOwner(shared_ptr<class Weapon> weapon) { _weapon = weapon; }
	void SetDestroyEffect(function<shared_ptr<Effect>()> effect) { _destroyEffect = effect; }
protected:
	virtual void DestroyEvent();

protected:
	map<shared_ptr<Object>, bool> _attacked;

	weak_ptr<class Weapon> _weapon;

	int _hitCount = 1;

	float _runTime = 0.0f;
	float _runTimeMax = 0.3f;
	float _speed = 0.0f;
	Vector2 _direction;

	function<shared_ptr<Effect>()> _destroyEffect;
};

