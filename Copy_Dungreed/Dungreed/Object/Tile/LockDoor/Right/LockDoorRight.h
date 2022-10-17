#pragma once
class LockDoorRight : public LockDoor
{
public:
	LockDoorRight();

protected:
	virtual void DoorOpenEffect() override;

};

