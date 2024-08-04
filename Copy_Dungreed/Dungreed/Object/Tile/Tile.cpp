#include "framework.h"
#include "Tile.h"

Tile::Tile(int level, int num)
	: Object(level,num)
{
	_objectType = Object::Object_Type::TILE;
	_staticObject = true;
}
