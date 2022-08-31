#include "framework.h"
#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Update()
{
	if(_anim != nullptr)
		_anim->Update();

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

void Item::SetOwner(shared_ptr<Creature> owner)
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
