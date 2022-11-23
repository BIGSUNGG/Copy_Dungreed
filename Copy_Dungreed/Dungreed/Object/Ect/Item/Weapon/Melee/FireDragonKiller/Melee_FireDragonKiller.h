#pragma once
class Melee_FireDragonKiller : public Melee
{
public:
	Melee_FireDragonKiller(int level, int num);

	virtual void Update() override;
	virtual void Render() override;

	virtual void FireEffect();

protected:
	vector<wstring> _fireEffectAnim;
	vector<shared_ptr<Effect>> _fireEffect;

	float _effectRunTime = 0.0f;
	const float _effectDelay = 0.1f;

};

