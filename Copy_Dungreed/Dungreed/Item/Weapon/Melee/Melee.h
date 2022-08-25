#pragma once
class Melee : public Weapon
{
public:
	Melee(int type , int num);
	virtual ~Melee();

	virtual void Attack() override;

	virtual void AttackEffect() override;

	virtual void SetWeapon();
};

