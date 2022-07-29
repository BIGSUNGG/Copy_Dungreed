#pragma once
class Tile : public Object
{
public:
	enum Type
	{
		TOP,
		BOTTOM,
		LEFT,
		LEFT_TOP,
		RIGHT,
		RIGHT_TOP,
	};

public:
	Tile(int level = 0, int type = 1, int num = 0);

	void Update() override;

protected:
	int _level = 0;
	int _type = 0;
	int _num = 0;
};

