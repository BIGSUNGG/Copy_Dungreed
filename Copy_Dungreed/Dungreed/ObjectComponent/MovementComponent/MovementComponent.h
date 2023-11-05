#pragma once

class Tile;

class MovementComponent : public ObjectComponent
{
public:
	MovementComponent(Object* object);

	virtual void Update() override;

	virtual void Jump();

public:
	// Getter Setter
	bool IsOnStair() { return _onStair; }
	bool IsFalling() { return _isFalling; }
	Vector2& GetMovement() { return _movement; }
	const Vector2& GetVelocity() { return _velocity; }

	void SetIsFalling(bool value) { _isFalling = value; }
	void SetMovementEvent(function<void()> func) { _movementEvent = func; }
	void SetCollisionEvent(function<void()> func) { _collisionEvent = func; }
	void SetBeforeMove(const Vector2& vec);
	void SetJumpPower(float power) { _jumpPower = power; }
	void SetJumpPowerMax(float power) { _jumpPowerMax = power; }
	void SetGravityRatio(float ratio) { _gravityRatio = ratio; }
	void SetCollision(bool collision) { _collision = collision; }
	void SetPassFloor(bool pass) { _passFloor = pass; }
	void SetPassTIle(bool pass) { _passTile = pass; }
	void SetStatic(bool sta) { _static = sta; }

protected:
	virtual void CollisionEvent();

	virtual bool TileCollison(shared_ptr<Tile> tile);
	virtual bool TileBlockCollision(shared_ptr<Tile> tile);
	virtual bool TileFloorCollision(shared_ptr<Tile> tile);
	virtual bool TileLeftStairCollision(shared_ptr<Tile> tile);
	virtual bool TileRightStairCollision(shared_ptr<Tile> tile);
	
protected:
	function<void()> _movementEvent;
	function<void()> _collisionEvent;

	Vector2 _velocity;
	Vector2 _movement;
	Vector2 _beforeMove;

	float _jumpPower = 0.0f;
	float _jumpPowerMax = 1800.0f;
	float _gravityPower = 5000.0f;
	float _gravityRatio = 1.0f;

	bool _static = false;
	bool _collision = true;
	bool _isFalling = false;
	bool _passFloor = false;
	bool _passTile = false;
	bool _onStair = false;
};

