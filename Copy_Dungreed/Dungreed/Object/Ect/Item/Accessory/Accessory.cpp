#include "framework.h"
#include "Accessory.h"

Accessory::Accessory(int num)
	: Item(0, num)
{
	_itemType = Item::ACCESSORY;
}
