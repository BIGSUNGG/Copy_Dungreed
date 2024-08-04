#include "framework.h"
#include "DropItem.h"

DropItem::DropItem(int type, int num)
	: Etc(type,num)
{
	_etcType = DROP_ITEM;
	_movement = make_shared<MovementComponent>(this);
	_movement->SetJumpPowerMax(1200.f);
}

void DropItem::Update()
{
	_movement->Update();
	Etc::Update();
}

void DropItem::SetItem(shared_ptr<Item> item)
{
	_item = item;
	SetTexture(make_shared<Quad>(item->GetObjectTexture()->GetImageFile()));
}

void DropItem::AddItemToCreature(Creature* creature)
{
	bool success = creature->AddItem(_item);
	if (success)
		_isActive = false;
}
