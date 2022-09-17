#pragma once
class Gun : public Weapon
{
public:
	Gun(int level, int num);
	virtual ~Gun();

	virtual void Render() override;

	virtual void Attack() override;

	virtual void AttackEffect();

	virtual void SetWeapon() override;

protected:
	float _bulletSpeed = 2000.0f;
};
