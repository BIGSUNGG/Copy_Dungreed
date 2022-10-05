#pragma once
class Gun : public Weapon
{
public:
	Gun(int level, int num);
	virtual ~Gun();

	virtual void Attack() override;

	virtual void SetWeapon() override;
protected:
	virtual void AttackEffect();

protected:
	float _bulletSpeed = 2500.0f;
};
