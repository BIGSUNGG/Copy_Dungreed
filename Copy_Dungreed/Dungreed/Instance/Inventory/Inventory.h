#pragma once

class Creature;
class Weapon;
class Accessory;
class Item;
enum class Item_Type;

enum class Slot_Type
{
	NONE,
	WEAPON_SLOT,
	SUB_WEAPON_SLOT,
	ACCESSORY_SLOT,
	ITEM_SLOT
};

class Inventory
{
public:
	Inventory(Creature* inOwner);

public:
	// 아이템을 장착가능할 시 자동으로 장착하고 장착할 수 없을 시 인벤토리에 추가
	// addItem : 추가할 아이템
	// return : 추가된 슬롯 (실패 시 NONE 반환), 추가된 슬롯의 인덱스 (실패시 -1 반환) 
	pair<Slot_Type, int> AddOrEquipItem(shared_ptr<Item> addItem);

	// 무기 장착
	// equipItem : 장착할 아이템
	// return : 장착된 슬롯의 인덱스 (장착 실패 시 -1 반환)
	int EquipWeapon(shared_ptr<Weapon> equipItem);

	// 악세사리 장착
	// equipItem : 장착할 아이템
	// return : 장착된 슬롯의 인덱스 (장착 실패 시 -1 반환)
	int EquipAccessory(shared_ptr<Accessory> equipItem);

	// 인벤토리에 아이템 추가
	// addItem : 추가할 아이템
	// return : 추가된 슬롯의 인덱스 (추가 실패 시 -1 반환)
	int AddItem(shared_ptr<Item> addItem);

	// left 아이템과 right 아이템의 위치를 교환
	// leftItem : 위치를 교환할 left 아이템
	// leftSlotType : left 아이템이 있는 슬롯의 위치
	// leftSlotNum : left 아이템이 있는 슬롯의 인덱스
	// rightItem : 위치를 교환할 right 아이템
	// rightSlotType : right 아이템이 있는 슬롯의 위치
	// rightSlotNum : right 아이템이 있는 슬롯의 인덱스
	// return : 성공 여부
	bool SwapItem(shared_ptr<Item> leftItem, Slot_Type leftSlotType, int leftSlotNum, shared_ptr<Item> rightItem, Slot_Type rightSlotType, int rightSlotNum);
	bool CanSwap(shared_ptr<Item> leftItem, Slot_Type leftSlotType, shared_ptr<Item> rightItem, Slot_Type rightSlotType);
	bool CanSwap(Item_Type leftItemType, Slot_Type leftSlotType, Item_Type bItemType, Slot_Type rightSlotType);

private:
	// 실질적으로 구현된 AddOrEquipItem 함수
	pair<Slot_Type, int> Internal_AddOrEquipItem(shared_ptr<Item> addItem);

public:
	// Getter Setter
	shared_ptr<class Weapon>	GetWeapon(int inIndex);
	shared_ptr<class Accessory>	GetAccessory(int inIndex);
	shared_ptr<class Item>		GetItem(int inIndex);

	const vector<shared_ptr<Weapon>>&		GetWeaponSlot() const { return _weaponSlot; }
	const vector<shared_ptr<Accessory>>&	GetAccessorySlot() const { return _accessorySlot; }
	const vector<shared_ptr<Item>>&			GetItemSlot() const { return _itemSlot; }

	void SetWeaponSlotSize(int inSize) { _weaponSlot.resize(inSize); }
	void SetAccessorySlotSize(int inSize) { _accessorySlot.resize(inSize); }
	void SetItemSlotSize(int inSize) { _itemSlot.resize(inSize); }

private:
	Creature* _owner;

	vector<shared_ptr<Weapon>> _weaponSlot; // 무기 슬롯
	vector<shared_ptr<Accessory>> _accessorySlot; // 악세사리 슬롯
	vector<shared_ptr<Item>> _itemSlot; // 아이템 슬롯
};

