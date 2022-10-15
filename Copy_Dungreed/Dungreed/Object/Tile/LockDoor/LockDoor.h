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
};

