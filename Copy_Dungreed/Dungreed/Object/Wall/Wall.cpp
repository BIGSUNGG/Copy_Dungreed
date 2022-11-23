#include "framework.h"
#include "Wall.h"

Wall::Wall(int level, int num)
	: Object(level,num)
{
	_renderOrder = 2.f;
	_objectType = Object::Object_Type::WALL;
	_static = true;
}
