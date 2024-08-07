#pragma once

class Tile;

class MovementComponent : public ObjectComponent
{
public:
	MovementComponent(Object* object);

	virtual void Update() override;

	virtual void Jump();

protected:
	virtual void CollisionEvent();

	virtual bool TileCollison(shared_ptr<Tile> tile);
	virtual bool TileBlockCollision(shared_ptr<Tile> tile);
	virtual bool TileFloorCollision(shared_ptr<Tile> tile);
	virtual bool TileLeftStairCollision(shared_ptr<Tile> tile);
	virtual bool TileRightStairCollision(shared_ptr<Tile> tile);

public:
	// Getter Setter
	bool IsOnStair() { return _onStair; }
	bool IsFalling() { return _isFalling; }
	Vector2& GetMoveDir() { return _moveDir; }
	const Vector2& GetVelocity() { return _curVelocity; }

	void SetIsFalling(bool value) { _isFalling = value; }
	void SetMovementEvent(function<void()> func) { _movementEvent = func; }
	void SetCollisionEvent(function<void()> func) { _collisionEvent = func; }
	void SetBeforeMove(const Vector2& vec);
	void SetJumpPower(float power) { _curJumpPower = power; }
	void SetJumpPowerMax(float power) { _maxJumpPower = power; }
	void SetGravityRatio(float ratio) { _gravityRatio = ratio; }
	void SetCollision(bool collision) { _collision = collision; }
	void SetPassFloor(bool pass) { _passFloor = pass; }
	void SetPassTIle(bool pass) { _passTile = pass; }
	void SetStatic(bool sta) { _static = sta; }
	
protected:
	function<void()> _movementEvent; // 이동 시 호출
	function<void()> _collisionEvent; // 다른 타일에 충돌 시 호출

	Vector2 _curVelocity; // 현재 속도
	Vector2 _moveDir; // 이동할 방향
	Vector2 _beforeMovePos; // 움직이기 전의 위치

	float _curJumpPower = 0.0f; // 현재 점프하는 힘
	float _maxJumpPower = 1800.0f; // 점프하는 힘
	float _gravityPower = 5000.0f; // 중력 힘
	float _gravityRatio = 1.0f; // 중력 비율

	bool _static = false;
	bool _collision = true; // 다른 타일과 충돌중인지
	bool _isFalling = false; // 공중에 있는지
	bool _passFloor = false; // 바닥을 통과할지
	bool _passTile = false; // 타일을 통과할지
	bool _onStair = false; // 계단에 있는지
};

