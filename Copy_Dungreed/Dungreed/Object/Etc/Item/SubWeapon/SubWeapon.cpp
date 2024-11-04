#include "framework.h"
#include "SubWeapon.h"

SubWeapon::SubWeapon(int num)
	: Item(0,num)
{
	_itemType = Item_Type::SUB_WEAPON;
}
