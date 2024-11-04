#include "framework.h"
#include "Inventory.h"

Inventory::Inventory(Creature* inOwner)
{
	_owner = inOwner;
}

std::pair<Slot_Type, int> Inventory::AddOrEquipItem(shared_ptr<Item> addItem)
{
	auto result = Internal_AddOrEquipItem(addItem);

	// 장착 성공 시 Owner 설정
	if (result.first != Slot_Type::NONE)
		addItem->SetOwner(static_pointer_cast<Creature>(_owner->shared_from_this()));

	return result;
}

int Inventory::EquipWeapon(shared_ptr<Weapon> equipItem)
{
	if (equipItem == nullptr)
		return -1;

	// 빈 슬롯에 아이템 장착
	for (int i = 0; i < _weaponSlot.size(); i++)
	{
		if (_weaponSlot[i] == nullptr)
		{
			_weaponSlot[i] = equipItem;
			return i;
		}
	}

	return -1;
}

int Inventory::EquipAccessory(shared_ptr<Accessory> equipItem)
{
	if (equipItem == nullptr)
		return -1;

	// 빈 슬롯에 아이템 장착
	for (int i = 0; i < _accessorySlot.size(); i++)
	{
		if (_accessorySlot[i] == nullptr)
		{
			_accessorySlot[i] = equipItem;
			return i;
		}
	}

	return -1;
}

int Inventory::AddItem(shared_ptr<Item> addItem)
{
	if (addItem == nullptr)
		return -1;

	// 빈 슬롯에 아이템 장착
	for (int i = 0; i < _itemSlot.size(); i++)
	{
		if (_itemSlot[i] == nullptr)
		{
			_itemSlot[i] = addItem;
			return i;
		}
	}

	return -1;
}

bool Inventory::SwapItem(shared_ptr<Item> leftItem, Slot_Type leftSlotType, int leftSlotNum, shared_ptr<Item> rightItem, Slot_Type rightSlotType, int rightSlotNum)
{
	// 아이템 교체가 가능한지
	bool canSwap = CanSwap(leftItem, leftSlotType, rightItem, rightSlotType);
	if (canSwap == false)
		return false;

	// left 아이템이 left 슬롯에 있는게 맞는지
	switch (leftSlotType)
	{
	case Slot_Type::WEAPON_SLOT:
		if (leftItem != _weaponSlot[leftSlotNum])
			return false;
		break;
	case Slot_Type::ACCESSORY_SLOT:
		if (leftItem != _accessorySlot[leftSlotNum])
			return false;
		break;
	case Slot_Type::ITEM_SLOT:
		if (leftItem != _itemSlot[leftSlotNum])
			return false;
		break;
	default:
		return false;
		break;
	}

	// right 아이템이 right 슬롯에 있는게 맞는지
	switch (rightSlotType)
	{
	case Slot_Type::WEAPON_SLOT:
		if (rightItem != _weaponSlot[rightSlotNum])
			return false;
		break;
	case Slot_Type::ACCESSORY_SLOT:
		if (rightItem != _accessorySlot[rightSlotNum])
			return false;
		break;
	case Slot_Type::ITEM_SLOT:
		if (rightItem != _itemSlot[rightSlotNum])
			return false;
		break;
	default:
		return false;
		break;
	}

	// A아이템을 B슬롯에 장착
	switch (rightSlotType)
	{
	case Slot_Type::WEAPON_SLOT:
		_weaponSlot[rightSlotNum] = static_pointer_cast<Weapon>(leftItem);
		break;
	case Slot_Type::ACCESSORY_SLOT:
		_accessorySlot[rightSlotNum] = static_pointer_cast<Accessory>(leftItem);
		break;
	case Slot_Type::ITEM_SLOT:
		_itemSlot[rightSlotNum] = leftItem;
		break;
	default:
		return false;
		break;
	}

	// B아이템을 A슬롯에 장착
	switch (leftSlotType)
	{
	case Slot_Type::WEAPON_SLOT:
		_weaponSlot[leftSlotNum] = static_pointer_cast<Weapon>(rightItem);
		break;
	case Slot_Type::ACCESSORY_SLOT:
		_accessorySlot[leftSlotNum] = static_pointer_cast<Accessory>(rightItem);
		break;
	case Slot_Type::ITEM_SLOT:
		_itemSlot[leftSlotNum] = rightItem;
		break;
	default:
		return false;
		break;
	}

	return true;
}

bool Inventory::CanSwap(shared_ptr<Item> leftItem, Slot_Type leftSlotType, shared_ptr<Item> rightItem, Slot_Type rightSlotType)
{
	return CanSwap(leftItem ? leftItem->GetItemType() : Item_Type::NONE, leftSlotType, rightItem ? rightItem->GetItemType() : Item_Type::NONE, rightSlotType);
}

bool Inventory::CanSwap(Item_Type leftItemType, Slot_Type leftSlotType, Item_Type bItemType, Slot_Type rightSlotType)
{
	// left 아이템이 right 아이템 슬롯에 장착이 가능한지
	if (leftItemType != Item_Type::NONE)
	{
		switch (rightSlotType)
		{
		case Slot_Type::WEAPON_SLOT:
			if (leftItemType != Item_Type::WEAPON)
				return false;
			break;
		case Slot_Type::ACCESSORY_SLOT:
			if (leftItemType != Item_Type::ACCESSORY)
				return false;
			break;
		case Slot_Type::ITEM_SLOT:
			break;
		default:
			return false;
			break;
		}
	}

	// right 아이템이 left 아이템 슬롯에 장착이 가능한지
	if (bItemType != Item_Type::NONE)
	{
		switch (leftSlotType)
		{
		case Slot_Type::WEAPON_SLOT:
			if (bItemType != Item_Type::WEAPON)
				return false;
			break;
		case Slot_Type::ACCESSORY_SLOT:
			if (bItemType != Item_Type::ACCESSORY)
				return false;
			break;
		case Slot_Type::ITEM_SLOT:
			break;
		default:
			return false;
			break;
		}
	}

	return true;
}

std::pair<Slot_Type, int> Inventory::Internal_AddOrEquipItem(shared_ptr<Item> addItem)
{
	switch (addItem->GetItemType())
	{
	case Item_Type::WEAPON:
	{
		// 장착 시도 후 장착 성공 시 장착된 슬롯 반환
		int num = EquipWeapon(static_pointer_cast<Weapon>(addItem));
		if (num != -1)
			return { Slot_Type::WEAPON_SLOT, num };
		break;
	}
	case Item_Type::SUB_WEAPON:
		break;
	case Item_Type::ACCESSORY:
	{
		// 장착 시도 후 장착 성공 시 장착된 슬롯 반환
		int num = EquipAccessory(static_pointer_cast<Accessory>(addItem));
		if (num != -1)
			return { Slot_Type::ACCESSORY_SLOT, num };
		break;
	}
	case Item_Type::NONE:
		break;
	default:
		break;
	}

	// 인벤토리에 추가 시도 후 추가 성공 시 추가된 슬롯 반환
	int num = AddItem(addItem);
	if (num != -1)
		return { Slot_Type::ITEM_SLOT, num };

	return { Slot_Type::NONE, num };
}

std::shared_ptr<Weapon> Inventory::GetWeapon(int inIndex)
{
	// 인덱스가 0보다 작다면 배열의 크기를 넘거나 null 반환
	if (inIndex < 0 || inIndex >= _weaponSlot.size())
		return nullptr;

	return _weaponSlot[inIndex];
}

std::shared_ptr<Accessory> Inventory::GetAccessory(int inIndex)
{
	// 인덱스가 0보다 작다면 배열의 크기를 넘거나 null 반환
	if (inIndex < 0 || inIndex >= _accessorySlot.size())
		return nullptr;

	return _accessorySlot[inIndex];
}

std::shared_ptr<Item> Inventory::GetItem(int inIndex)
{
	// 인덱스가 0보다 작다면 배열의 크기를 넘거나 null 반환
	if (inIndex < 0 || inIndex >= _itemSlot.size())
		return nullptr;

	return _itemSlot[inIndex];
}

