#pragma once
class LockDoor : public Tile
{
public:
	enum LockDoor_State
	{
		LOCK,
		IDLE,
		OPEN,
	};

public:
	LockDoor(int level = 0, int num = 0);

	virtual void Update() override;

	virtual void Open();

protected:
	virtual void DoorOpenEffect();

protected:
	bool _open = false;
	float _doorEffectDelayTime = 0.15f;
	const float _doorEffectDelay = 0.15f;

	Vector2 _moveDirection = { 0,0 };

};

