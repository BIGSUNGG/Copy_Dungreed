#pragma once
class Ect : public Object
{
public:
	enum Ect_Type
	{
		UNKNOWN,
		ITEM,
		BULLET,
		CHEST,
		DROP_ITEM,
		DROP_COIN,
	};

public:
	Ect(int level, int num);

	virtual void Interaction() {}

public:
	// Getter Setter
	const Ect_Type& GetEctType() { return _ectType; }
	bool GetInteraction() { return _interaction; }

protected:
	Ect_Type _ectType = UNKNOWN;
	bool _interaction = false;
};

