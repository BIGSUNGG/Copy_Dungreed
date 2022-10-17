#pragma once
class LockDoorLeft : public LockDoor
{
public:
	LockDoorLeft();

protected:
	virtual void DoorOpenEffect() override;

};

