#include "framework.h"
#include "Creature_Status.h"

Creature_Status::Creature_Status()
{
}

Creature_Status::~Creature_Status()
{
}

void Creature_Status::SetMaxHp(int maxHp)
{
	_hpMax	= maxHp;
	_hp		= maxHp;
}
