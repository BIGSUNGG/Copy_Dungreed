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

	virtual void SetOwnerMap(shared_ptr<Map> map) override;

protected:
	virtual void Opened();
	virtual void Open();
	virtual void Lock();
	virtual void DoorOpenEffect();

	Vector2 _moveDirection = { 0,0 };

	const float _doorEffectDelay = 0.15f;
	float _doorEffectDelayTime = 0.15f;
	bool _open = false;

};

