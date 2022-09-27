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

	void SetDestroyEffect(function<shared_ptr<Effect>()> effect) { _destroyEffect = effect; }
	virtual void SetSpeed(float speed) { _speed = speed; }
	virtual void SetDirection(const Vector2& direction) { _direction = direction; }
	virtual void SetOwner(shared_ptr<Item> weapon) { _weapon = weapon; }
protected:
	virtual void DestroyEvent();

protected:
	weak_ptr<Item> _weapon;

	float _runTime = 0.0f;
	float _runTimeMax = 0.3f;
	float _speed = 0.0f;
	Vector2 _direction;

	function<shared_ptr<Effect>()> _destroyEffect;
};

