#include "framework.h"
#include "BackGround.h"

BackGround::BackGround(int level, int num)
	: Object(level, num)
{
	_objectType = Object::Object_Type::BACKGROUND;
}


BackGround::~BackGround()
{
}
