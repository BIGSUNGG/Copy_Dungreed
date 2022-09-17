#include "framework.h"
#include "Status.h"

Status::Status()
{
}

Status::~Status()
{
}

void Status::SetMaxHp(int maxHp)
{
	_hpMax	= maxHp;
	_hp		= maxHp;
}
