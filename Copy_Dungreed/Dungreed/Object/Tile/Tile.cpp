#include "framework.h"
#include "Tile.h"

Tile::Tile(int level, int num)
	: Object(level,num)
{
	_texture = TEXTURE_MANAGER->GetTileTexture(level, num);

	_objectType = Object::Object_Type::TILE;

	_collider = make_shared<RectCollider>(_texture->GetHalfSize());
	_collider->SetParent(_texture->GetTransform());

}
