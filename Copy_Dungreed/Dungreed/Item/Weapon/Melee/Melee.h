#pragma once
class Melee : public Weapon
{
public:
	Melee();
	virtual ~Melee();

	virtual void Attack() override;

	virtual void AttackEffect() override;

	virtual void SetWeapon();
};

