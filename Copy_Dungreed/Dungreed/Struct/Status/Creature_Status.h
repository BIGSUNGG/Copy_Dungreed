#pragma once
struct Creature_Status
{
public:
	Creature_Status();
	~Creature_Status();

	void SetMaxHp(int maxHp);
	float GetHpRatio() const { return (float)_hp / (float)_hpMax; }

public:
	int _hp = 0;
	int _hpMax = 0;
	int _def = 0;
	int _atk = 0;
	float _speed = 0;
};