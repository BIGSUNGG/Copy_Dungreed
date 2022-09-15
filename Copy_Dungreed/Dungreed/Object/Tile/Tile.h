#pragma once
class Tile : public Object
{
public:
	enum Tile_Type
	{
		BLOCK,
		FLOOR,
		LEFT_STAIR,
		RIGHT_STAIR,
	};
	
public:
	Tile(int level, int num);

	virtual Tile_Type& GetTileType() { return _tileType; }

protected:
	Tile_Type _tileType = BLOCK;
};
