#include "framework.h"
#include "Ect.h"

Ect::Ect(int level, int num)
	: Object(level,num)
{
	_objectType = Object_Type::ECT;
}
