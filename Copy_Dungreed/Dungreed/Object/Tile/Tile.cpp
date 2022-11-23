#include "framework.h"
#include "Tile.h"

Tile::Tile(int level, int num)
	: Object(level,num)
{
	_renderOrder = 3.f;
	_objectType = Object::Object_Type::TILE;
	_static = true;
}
