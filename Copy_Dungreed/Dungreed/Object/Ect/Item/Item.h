#pragma once

class Creature;

class Item : public Object , public enable_shared_from_this<Item>
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
	Item();
	virtual ~Item();

	virtual void Render();

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
