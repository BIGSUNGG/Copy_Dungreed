#pragma once
class Gun : public Weapon
{
public:
	Gun(int type, int num);
	virtual ~Gun();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Attack() override;

	virtual void AttackEffect();

	virtual void SetWeapon() override; 

protected:
	vector<shared_ptr<Bullet>> _bullets;
	float _bulletSpeed = 1000.0f;
};

