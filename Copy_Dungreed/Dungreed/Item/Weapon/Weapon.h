#pragma once
class Weapon : public Item
{
public:
	enum Weapon_Type
	{
		MELEE,
		GUN,
		SUB
	};

public:
	Weapon();

	virtual void Update();

	virtual void Attack() override;
	virtual void Skill() override;
	virtual void Damaged(const Status& status) override;

	virtual void AttackEffect();

	virtual void SetWeapon();
	virtual void SetOwner(shared_ptr<Creature> owner) override;

	virtual const bool& GetFastRender() { return _fastRender[_index]; }

protected:
	Weapon_Type _weaponType = MELEE;

	float _weaponLength = 0.0f;
	bool _reversed = false;

	shared_ptr<Transform> _springArm;
	shared_ptr<Transform> _attackOfsset;
	shared_ptr<Transform> _ownerFollower;

	int _index = 0;
	vector<bool> _fastRender = { false,true };

	float _attackDelay = 0.3f;
	float _attackedTime = 0.1f;

	vector<float> _appendAngle = { 0.0f };
	Vector2 _attackRange = { 0,0 };
	Vector2 _offset;
};

