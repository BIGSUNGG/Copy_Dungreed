#include "framework.h"
#include "Ect.h"

Ect::Ect(int level, int num)
	: Object(level,num)
{
	_renderOrder = 5.f;
	_objectType = Object_Type::ECT;
	_static = false;
}
