#pragma once
class Player : public Creature , public std::enable_shared_from_this<Player>
{
public:
	Player(int level, int num);

	virtual void Update() override;
	virtual void Render() override;

	virtual void DustEffect();
	virtual void DoubleJumpEffect();

	virtual void MouseEvent();
	virtual void MovementEvent();
	virtual void InputEvent();

	virtual void Attack();
	virtual void Jump();

	virtual const Vector2& GetHandPos() { return _handPos; }

	virtual void SetWeapon(shared_ptr<Item> weapon);

protected:
	shared_ptr<Item> _weapon;

	bool _doubleJumped = false;

	float _dustRunTime = 0.25f;
	float _dustDelay = 0.25f;

	Vector2 _handPos = { 45,-25 };

};

