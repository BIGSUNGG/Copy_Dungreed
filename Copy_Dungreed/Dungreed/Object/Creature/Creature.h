#pragma once
class Creature : public Object
{
public:
	enum Creature_Type
	{
		PLAYER,
		ENEMY,
		BOSS,
		NPC,
	};

public:
	Creature(int level, int num);

	virtual void Update() override;

	virtual void CollisionEvent(shared_ptr<Object> objects);

	virtual Creature_Type& GetCreatureType() { return _creatureType; }
	
protected:
	Creature_Type _creatureType = ENEMY;

	Vector2 _movedPos;
	Vector2 _movementPos;

	float _jumpPower = 0.0f;
	float _jumpPowerMax = 800.0f;
	float _gravity = 1200.0f;

	bool _isReversed = false;
	bool _isPass = false;
	bool _onBlock = false;
	bool _isFalling = false;
	float _speed = 350.0f;
};

