#include "framework.h"
#include "Item.h"

Item::Item()
{
	_objectType = Object_Type::ECT;
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
