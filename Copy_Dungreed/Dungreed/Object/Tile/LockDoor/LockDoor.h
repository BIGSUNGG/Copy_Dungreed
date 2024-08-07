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


protected:
	virtual void Opened();
	virtual void Open();
	virtual void Lock();
	virtual void DoorOpenEffect();

public:
	// Getter Setter
	virtual void SetOwnerMap(shared_ptr<Map> map) override;

protected:
	Vector2 _moveDirection = { 0,0 }; // 미로에서 이동할 위치

	const float _doorEffectDelay = 0.15f;
	float _doorEffectDelayTime = 0.15f;
	bool _open = false;

};

