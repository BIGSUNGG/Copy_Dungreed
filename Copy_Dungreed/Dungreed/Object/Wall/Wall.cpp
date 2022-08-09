#include "framework.h"
#include "Wall.h"

Wall::Wall(int level, int num)
	: Object(level,num)
{
	_objectType = Object::Object_Type::WALL;
}
