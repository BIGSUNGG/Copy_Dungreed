#pragma once

class Creature;

class Item : public Ect , public enable_shared_from_this<Item>
{
public:
	enum Item_Type
	{
		PLAYER,
		FOOD,
		WEAPON,
		ACCESSORY,
	};

	enum Item_State
	{
		IDLE,
		ATTACK,
		SKILL,
		DAMAGED,
	};

public:
	Item(int level, int num);
	virtual ~Item();

	virtual bool GiveDamage(shared_ptr<Creature> target);

	virtual void ReverseTexture();

	virtual void Attack() abstract;
	virtual void Skill() abstract;
	virtual void Damaged(const Status& status) abstract;

	virtual void SetOwner(shared_ptr<Creature> owner);

	const shared_ptr<Creature> GetOwner() { return _owner.lock(); }
	const Item_Type& GetItemType() { return _itemType; }

protected:
	weak_ptr<Creature> _owner;

	Status _status;

	Item_Type _itemType = ACCESSORY;
};

