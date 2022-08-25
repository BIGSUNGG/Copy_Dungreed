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

	virtual void Damaged(Status status);

	virtual void MoveCharacter();
	virtual void CollisionEvent(shared_ptr<Object> objects);
	virtual void TileCollison(shared_ptr<Tile> tile);
	virtual void CreatureCollision(shared_ptr<Creature> creature);

	const Vector2& GetVelocity() { return _velocity; }
	const Status& GetStatus() { return _status; }
	Vector2& GetBeforeMove() { return _beforeMove; }
	Creature_Type& GetCreatureType() { return _creatureType; }

	virtual void SetOriginalPos(Vector2 pos) override;
	
protected:
	Creature_Type _creatureType = ENEMY;

	Vector2 _movement;
	Vector2 _beforeMove;
	Vector2 _velocity = { 0,0 };

	Status _status;

	float _jumpPower = 0.0f;
	float _jumpPowerMax = 1200.0f;

	float _gravityPower = 3000.0f;

	bool _isFalling = false;
	bool _passFloor = false;
	bool _gravity = true;
	float _speed = 450.0f;
};

