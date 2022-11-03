#include "framework.h"
#include "Item.h"

Item::Item(int level, int num)
	: Ect(level, num)
{
	_ectType = Ect::ITEM;
}

Item::~Item()
{
}

bool Item::GiveDamage(shared_ptr<Creature> target)
{
	bool attackSuccess = _owner.lock()->GiveDamage(target, shared_from_this());
	return attackSuccess;
}

void Item::ReverseTexture()
{
	_texture->ReverseToX();
	SwitchBool(_reversed);
}

void Item::SetOwner(shared_ptr<Creature> owner)
{
	_owner = owner;
}

void Item::SetHudTexture(const wstring& image)
{
	_hudTexture = make_shared<Quad>(image);
	_hudTexture->Update();
}
