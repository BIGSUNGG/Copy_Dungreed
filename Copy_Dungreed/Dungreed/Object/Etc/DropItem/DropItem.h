#pragma once

class Creature;

class DropItem : public Etc
{
public:
	DropItem(int type, int num);

	virtual void Update() override;

	virtual void SetItem(shared_ptr<Item> item);

	virtual void AddItemToCreature(Creature* creature);
	shared_ptr<MovementComponent> GetMovementComponent() { return _movement; }

protected:
	shared_ptr<MovementComponent> _movement;
	shared_ptr<Item> _item;

};

