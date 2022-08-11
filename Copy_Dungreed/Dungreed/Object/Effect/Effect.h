#pragma once
class Effect : public Object
{
public:
	enum Effect_Type
	{
		WEATHER,
		MOVEMENT,
		MONSTER_ATTACK,
		PLAYER_ATTACK,
		ATTACKED,
	};

public:
	Effect(int level, int num);

protected:
	Effect_Type _effectType = MOVEMENT;

};

