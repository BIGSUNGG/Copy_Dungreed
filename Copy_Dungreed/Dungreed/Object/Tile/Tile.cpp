#include "framework.h"
#include "Tile.h"

Tile::Tile(int level, int type, int num)
{
	_texture = TEXTURE_MANAGER->GetTileTexture(level, type, num);

	_collider = make_shared<RectCollider>(_texture->GetHalfSize());
	_collider->SetParent(_texture->GetTransform());

	_level = level;
	_type = type;
	_num = num;
}

void Tile::Update()
{
	_texture->Update();
}
