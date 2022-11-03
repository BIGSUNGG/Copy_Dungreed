#pragma once
class Melee_FireDragonKiller : public Melee
{
public:
	Melee_FireDragonKiller(int level, int num);

	virtual void Update() override;

	virtual void FireEffect();

protected:
	vector<wstring> _fireEffectAnim;

	float _effectRunTime = 0.0f;
	const float _effectDelay = 0.1f;

};

