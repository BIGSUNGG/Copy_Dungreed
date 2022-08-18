#pragma once
class Monster : public Creature
{
public:
	Monster(int level, int num);

	virtual void Update() override;
	
	virtual void MovementEvent();

protected:
};

