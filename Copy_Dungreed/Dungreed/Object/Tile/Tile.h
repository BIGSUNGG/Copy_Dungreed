#pragma once
class Tile : public Object
{
public:
	enum Tile_Type
	{
		FLOOR,
		BLOCK,
		LEFT_STAIR,
		RIGHT_STAIR,
	};
	
public:
	Tile(int level, int num);

public:
	// Getter Setter
	virtual Tile_Type& GetTileType() { return _tileType; }

protected:
	Tile_Type _tileType = BLOCK;
};
