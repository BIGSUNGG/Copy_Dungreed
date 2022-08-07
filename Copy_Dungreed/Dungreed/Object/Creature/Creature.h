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

	enum State
	{
		IDLE,
		ATTACK,
		MOVE,
		JUMP,
		DIE,
		CHARGE
	};

public:
	Creature(int level, int num);

	virtual Creature_Type& GetCreatureType() { return _creatureType; }

protected:
	Creature_Type _creatureType = ENEMY;
	State _state = IDLE;

	float _hp, _maxHp;
	float _def, _maxHp;
};

