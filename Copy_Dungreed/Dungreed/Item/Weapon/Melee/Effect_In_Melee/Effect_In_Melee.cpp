#include "framework.h"
#include "Effect_In_Melee.h"

Effect_In_Melee::Effect_In_Melee()
	: Melee()
{
	_offset = { 70,-25 };
	_appendAngle = { 0.7f };
	_giveDamageDelay = 0.8f;
	_attackRange = { 100,100 };
}

void Effect_In_Melee::AttackEffect()
{
}

