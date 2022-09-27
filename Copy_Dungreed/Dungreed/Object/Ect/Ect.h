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

	const Ect_Type& GetEctType() { return _ectType; }

protected:
	Ect_Type _ectType = UNKNOWN;
};

