#pragma once
class Tile : public Object
{
public:
	enum Tile_Type
	{
		FLOOR,
		LEFT_STAIR,
		RIGHT_STAIR,
		CELLING,
	};

	Tile(int level, int num);
};
