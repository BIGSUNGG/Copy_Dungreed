#pragma once

class ObjectManager;

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
	Weapon(int level, int num);

	virtual void Update();

	virtual void Attack() override;
	virtual void Skill() override;
	virtual void Damaged(const Status& status) override;

	virtual void SetAttackEffect(function<shared_ptr<Effect>()> effect) { _attackEffect = effect; }

	virtual void SetWeapon();
	void SetOffset(Vector2 offset) { _offset = offset; }
	void SetAppendAngle(vector<float> angle) { _appendAngle = angle; }
	void SetAttackDelay(float delay) { _attackDelay = delay; }
	void SetAttackRange(Vector2 range) { _attackRange = range; }
	void SetGiveDamageDelay(float delay) { _giveDamageDelay = delay; }
	virtual void SetOwner(shared_ptr<Creature> owner) override;
	void SetShowTo(const float& showDirection) { _showDirection = showDirection; }

	const Weapon_Type& GetWeaponType() { return _weaponType; }
	virtual const bool& GetFastRender() { return _fastRender[_index]; }
protected:
	virtual void AttackEffect();
	virtual void CheckAttack();

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
	float _attackDelayTime = 0.3f;

	vector<float> _appendAngle = { 0.0f };
	Vector2 _attackRange = { 0,0 };
	Vector2 _offset;
	float _showDirection;

	bool _attacked = false;
	float _giveDamageDelay = 0.0f;
	float _giveDamageDelayRunTime = 0.0f;

	function<shared_ptr<Effect>()> _attackEffect;
};

