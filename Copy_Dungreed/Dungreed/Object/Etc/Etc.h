#pragma once
class Etc : public Object
{
public:
	enum Etc_Type
	{
		UNKNOWN,
		ITEM,
		BULLET,
		CHEST,
		DROP_ITEM,
		DROP_COIN,
	};

public:
	Etc(int level, int num);

	virtual void Interaction() {}

public:
	// Getter Setter
	const Etc_Type& GetEtcType() { return _etcType; }
	bool GetInteraction() { return _interaction; }

protected:
	Etc_Type _etcType = UNKNOWN;
	bool _interaction = false;
};

