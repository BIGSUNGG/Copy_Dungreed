#pragma once
class Melee : public Weapon
{
public:
	Melee(int level, int num);
	virtual ~Melee();

	virtual void Attack() override;
	virtual void CheckAttack() override;

	virtual void AttackEffect() override;

public:
	// Getter Setter
	virtual void SetWeapon() override;
};

