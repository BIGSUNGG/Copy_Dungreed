#include "framework.h"
#include "Item.h"

Item::Item(int type, int num)
	: _type(type), _num(num)
{
}

Item::~Item()
{
}

void Item::Update()
{
	_texture->Update();
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

void Item::SetOwner(shared_ptr<Player> owner)
{
	_owner = owner;
}

void Item::SetAnimation()
{
	_anim = make_shared<Animation>();
}

void Item::SetTexture(shared_ptr<Quad> texture)
{
	_texture = texture;
}
