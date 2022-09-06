#pragma once

class Item;

class Bullet : public Ect
{
public:
	Bullet();
	virtual ~Bullet();

	void Update();

	void ReverseTexture();
	virtual void Attack();
	virtual void DestroyEvent();

	virtual void SetSpeed(float speed) { _speed = speed; }
	virtual void SetDirection(const Vector2& direction) { _direction = direction; }
	virtual void SetOwner(shared_ptr<Item> weapon) { _weapon = weapon; }

protected:
	weak_ptr<Item> _weapon;

	float _runTime = 0.0f;
	float _runTimeMax = 1.0f;
	float _speed = 0.0f;
	Vector2 _direction;
};

