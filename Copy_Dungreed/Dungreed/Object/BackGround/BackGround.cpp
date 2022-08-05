#include "framework.h"
#include "BackGround.h"

BackGround::BackGround(int level, int num)
	: Object(level, num)
{
	_texture = TEXTURE_MANAGER->GetBackGroundTexture(level, num);

	_objectType = Object::Object_Type::BACKGROUND;

	_collider = make_shared<RectCollider>(_texture->GetHalfSize());
	_collider->SetParent(_texture->GetTransform());
}


BackGround::~BackGround()
{
}
