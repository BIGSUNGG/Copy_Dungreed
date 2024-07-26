#include "framework.h"
#include "Etc.h"

Etc::Etc(int level, int num)
	: Object(level,num)
{
	_renderOrder = 5.f;
	_objectType = Object_Type::ETC;
	_staticObject = false;
}
