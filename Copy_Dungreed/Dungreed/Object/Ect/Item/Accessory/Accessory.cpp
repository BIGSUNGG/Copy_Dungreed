#include "framework.h"
#include "Accessory.h"

Accessory::Accessory(int level, int num)
	: Item(level, num)
{
	_itemType = Item::ACCESSORY;
}
