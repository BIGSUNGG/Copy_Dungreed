#include "framework.h"
#include "DropItem.h"

DropItem::DropItem(int type, int num)
	: Ect(type,num)
{
	_ectType = DROP_ITEM;
	_movement = make_shared<MovementComponent>(this);
	_movement->SetJumpPowerMax(1200.f);
	_renderOrder = 3.75f;
}

void DropItem::Update()
{
	_movement->Update();
	Ect::Update();
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
