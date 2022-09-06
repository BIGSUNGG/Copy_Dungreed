#pragma once
class Gun : public Weapon
{
public:
	Gun();
	virtual ~Gun();

	virtual void Render() override;

	virtual void Attack() override;

	virtual void AttackEffect();

	virtual void SetWeapon() override;

protected:
	float _bulletSpeed = 1000.0f;
};
