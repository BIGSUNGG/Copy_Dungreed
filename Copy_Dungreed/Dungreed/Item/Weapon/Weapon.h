#pragma once
class Weapon : public Item
{
public:
	Weapon(int level, int num);

	virtual void Update();

	virtual void Attack() override;
	virtual void Skill() override;
	virtual void Damaged(const Status& status) override;

	virtual void SwingEffect();

	virtual void SetOwner(shared_ptr<Player> owner) override;

protected:
	float _weaponLength = 0.0f;
	bool _reversed = false;

	shared_ptr<Transform> _springArm;
	shared_ptr<Transform> _swingArm;
	shared_ptr<Transform> _ownerFollower;

	int _angleIndex = 0;
	float _attackDelay = 0.1f;
	float _attackedTime = 0.1f;

	vector<float> _appendAngle = { -0.1f,0.7f };
	Vector2 _attackRange = { 0,0 };
};

