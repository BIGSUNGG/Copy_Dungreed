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
	Creature_Type& GetCreatureType() { return _creatureType; }
	
protected:
	Creature_Type _creatureType = ENEMY;

	Vector2 _movement;
	Vector2 _beforeMove;
	Vector2 _velocity;

	float _jumpPower = 0.0f;
	float _jumpPowerMax = 1000.0f;
	float _gravity = 2000.0f;

	bool _isReversed = false;
	bool _passFloor = false;
	bool _isFalling = false;
	float _speed = 350.0f;
};

