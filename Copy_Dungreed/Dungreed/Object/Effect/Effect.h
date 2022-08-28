#pragma once
class Effect : public Object
{
public:
	enum Effect_Type
	{
		NONE,
		MAP,
		ITEM,
		PLAYER,
		MONSTER,
	};

public:
	Effect(int level, int num);
	
	virtual void Update()override;

	virtual Effect_Type& GetEffectType() { return _effectType; }

protected:
	Effect_Type _effectType = PLAYER;

};

