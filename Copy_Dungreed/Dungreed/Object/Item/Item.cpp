#include "framework.h"
#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Render()
{
	_texture->Render();
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
