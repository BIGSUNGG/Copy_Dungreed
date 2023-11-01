#pragma once
class Gun : public Weapon
{
public:
	Gun(int level, int num);
	virtual ~Gun();

	virtual void Attack() override;

protected:
	virtual void AttackEffect();

public:
	// Getter Setter
	virtual void SetWeapon() override;

protected:
	float _bulletSpeed = 2500.0f;
};
