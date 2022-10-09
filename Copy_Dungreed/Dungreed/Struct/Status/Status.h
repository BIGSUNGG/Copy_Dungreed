#pragma once
struct Status
{
public:
	Status();
	~Status();

	void SetMaxHp(int maxHp);
	float GetHpRatio() const { return (float)_hp / (float)_hpMax; }

public:
	int _hp = 0;
	int _hpMax = 0;
	int _def = 0;
	int _atk = 0;
};