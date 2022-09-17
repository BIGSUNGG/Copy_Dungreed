#pragma once
class Ect : public Object
{
public:
	enum Ect_Type
	{
		UNKNOWN,
		ITEM,
		BULLET
	};

public:
	Ect(int level,int num);

protected:
	Ect_Type _ectType = UNKNOWN;
};

