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
	virtual void ImGuiRender() override;

	void MoveCharacter(Vector2 pos);
	virtual void CollisionEvent(shared_ptr<Object> objects);

	const Vector2& GetVelocity() { return _velocity; }
	Vector2& GetBeforeMove() { return _beforeMove; }
	Creature_Type& GetCreatureType() { return _creatureType; }
	
protected:
	Creature_Type _creatureType = ENEMY;

	Vector2 _movement;
	Vector2 _beforeMove;
	Vector2 _velocity;

	float _jumpPower = 0.0f;
	float _jumpPowerMax = 1200.0f;
	float _gravity = 3000.0f;

	bool _isFalling = false;
	bool _passFloor = false;
	float _speed = 450.0f;
};

