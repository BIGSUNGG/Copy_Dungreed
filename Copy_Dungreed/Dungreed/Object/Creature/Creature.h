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

	virtual void MoveCharacter(Vector2 pos);
	virtual void CollisionEvent(shared_ptr<Object> objects);

	virtual Creature_Type& GetCreatureType() { return _creatureType; }
	
protected:
	Creature_Type _creatureType = ENEMY;

	Vector2 _movedPos;
	Vector2 _movementPos;

	bool _isPass = false;
	bool _onBlock = false;
	bool _isFalling = false;
	float _speed = 350.0f;
};

