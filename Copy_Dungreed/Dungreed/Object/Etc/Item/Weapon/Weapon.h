#pragma once

class ObjectManager;

class Weapon : public Item
{
public:
	enum Weapon_Type
	{
		MELEE,
		GUN,
	};

public:
	Weapon(int level, int num);

	virtual void Update();

	virtual void Attack() override;
	virtual void Skill() override;
	
	virtual bool GiveDamage(int damage, shared_ptr<Creature> target);

	virtual void SetAttackEffect(function<shared_ptr<Effect>()> effect) { _attackEffect = effect; }

	void AddOffsetIndex(const int& num);

protected:
	virtual void AttackEffect();
	virtual void CheckAttack();

public:
	// Getter Setter
	virtual void SetWeapon();
	void SetOffset(Vector2 offset) { _offset = offset; }
	void SetShowTo(const float& showDirection) { _showDirection = showDirection; }

	void SetAttackDelay(float delay);
	void SetAttackRange(Vector2 range) { _attackRange = range; }
	void SetGiveDamageDelay(float delay) { _giveDamageDelay = delay; }
	void SetAttackMinDamage(float Damage) { _attackMinDamage = Damage; }
	void SetAttackMaxDamage(float Damage) { _attackMaxDamage = Damage; }
	void SetAppendAngle(vector<float> angle) { _appendAngle = angle; }
	virtual void SetAttackSound(const string& sound) { _attackSound = sound; }

	void SetSkill(function<void()> skill, const wstring& image);
	void SetSkillDelay(const float& delay);
	virtual void SetOwner(shared_ptr<Creature> owner) override;

	float GetSkillCoolTimeRatio();
	virtual const Vector2& GetOffset() { return _offset; }
	const Weapon_Type& GetWeaponType() { return _weaponType; }
	shared_ptr<Transform> GetSpringArm() { return _springArm; }
	virtual const float& GetShowDirection() { return _showDirection; }
	shared_ptr<Quad> GetSkillHuiTexture() { return _skillHudTexture; }
	virtual const bool GetFastRender() { return _fastRender[_offsetIndex]; }

	float GetRandomDamage() { return MathUtility::RandomFloat(_attackMinDamage, _attackMaxDamage); }
protected:
	Weapon_Type _weaponType = MELEE;
	shared_ptr<Quad> _skillHudTexture;
	function<void()> _skill;
	float _skillDelay = 0.f;
	float _skillRuntime = 0.f;

	float _weaponLength = 0.0f;
	bool _reverseTexture = false;
	shared_ptr<Transform> _springArm;
	shared_ptr<Transform> _attackOfsset;
	shared_ptr<Transform> _ownerFollower;

	vector<bool> _fastRender = { false,true }; // 소유하고 있는 캐릭터보다 빠르게 렌더링될지 

	float _attackDelay = 0.3f;
	float _attackDelayTime = 0.3f;
	string _attackSound;

	vector<float> _appendAngle = { 0.0f };
	Vector2 _attackRange = { 0,0 };
	Vector2 _offset;
	int _offsetIndex = 0;
	float _showDirection = 0.f;

	bool _attacked = false;
	float _attackMinDamage = 10.f;
	float _attackMaxDamage = 10.f;
	float _giveDamageDelay = 0.0f;
	float _giveDamageDelayRunTime = 0.0f;

	function<shared_ptr<Effect>()> _attackEffect;
};

