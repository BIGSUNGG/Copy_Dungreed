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

	virtual Creature_Type& GetCreatureType() { return _creatureType; }

protected:
	Creature_Type _creatureType = ENEMY;

	Vector2 _movedPos;
	Vector2 _movementPos;

	bool _isFalling;
	float _speed = 350.0f;
};

