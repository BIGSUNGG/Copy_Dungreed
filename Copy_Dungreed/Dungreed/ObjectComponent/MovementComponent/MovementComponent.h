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
	function<void()> _movementEvent; // �̵� �� ȣ��
	function<void()> _collisionEvent; // �ٸ� Ÿ�Ͽ� �浹 �� ȣ��

	Vector2 _curVelocity; // ���� �ӵ�
	Vector2 _moveDir; // �̵��� ����
	Vector2 _beforeMovePos; // �����̱� ���� ��ġ

	float _curJumpPower = 0.0f; // ���� �����ϴ� ��
	float _maxJumpPower = 1800.0f; // �����ϴ� ��
	float _gravityPower = 5000.0f; // �߷� ��
	float _gravityRatio = 1.0f; // �߷� ����

	bool _static = false;
	bool _collision = true; // �ٸ� Ÿ�ϰ� �浹������
	bool _isFalling = false; // ���߿� �ִ���
	bool _passFloor = false; // �ٴ��� �������
	bool _passTile = false; // Ÿ���� �������
	bool _onStair = false; // ��ܿ� �ִ���
};

