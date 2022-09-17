#pragma once
class Status
{
public:
	Status();
	~Status();

	void SetMaxHp(int maxHp);

public:
	int _hp = 0;
	int _hpMax = 0;
	int _def = 0;
	int _atk = 0;
};