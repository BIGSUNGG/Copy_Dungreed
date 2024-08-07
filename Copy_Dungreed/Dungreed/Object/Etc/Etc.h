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

	// 플레이어가 상호작용할 때 호출
	virtual void Interaction() {}

public:
	// Getter Setter
	const Etc_Type& GetEtcType() { return _etcType; }
	bool GetInteraction() { return _interaction; }

protected:
	Etc_Type _etcType = UNKNOWN;
	bool _interaction = false; // 플레이어와 상호작용이 가능한지
};

