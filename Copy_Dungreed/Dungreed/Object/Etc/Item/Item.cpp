#include "framework.h"
#include "Item.h"

Item::Item(int level, int num)
	: Etc(level, num)
{
	_etcType = Etc::ITEM;
}

Item::~Item()
{
}

void Item::ReverseTexture()
{
	_texture->ReverseToX();
	SWITCH_BOOL(_reversed);
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
