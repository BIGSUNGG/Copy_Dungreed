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
	// �������� ���������� �� �ڵ����� �����ϰ� ������ �� ���� �� �κ��丮�� �߰�
	// addItem : �߰��� ������
	// return : �߰��� ���� (���� �� NONE ��ȯ), �߰��� ������ �ε��� (���н� -1 ��ȯ) 
	pair<Slot_Type, int> AddOrEquipItem(shared_ptr<Item> addItem);

	// ���� ����
	// equipItem : ������ ������
	// return : ������ ������ �ε��� (���� ���� �� -1 ��ȯ)
	int EquipWeapon(shared_ptr<Weapon> equipItem);

	// �Ǽ��縮 ����
	// equipItem : ������ ������
	// return : ������ ������ �ε��� (���� ���� �� -1 ��ȯ)
	int EquipAccessory(shared_ptr<Accessory> equipItem);

	// �κ��丮�� ������ �߰�
	// addItem : �߰��� ������
	// return : �߰��� ������ �ε��� (�߰� ���� �� -1 ��ȯ)
	int AddItem(shared_ptr<Item> addItem);

	// left �����۰� right �������� ��ġ�� ��ȯ
	// leftItem : ��ġ�� ��ȯ�� left ������
	// leftSlotType : left �������� �ִ� ������ ��ġ
	// leftSlotNum : left �������� �ִ� ������ �ε���
	// rightItem : ��ġ�� ��ȯ�� right ������
	// rightSlotType : right �������� �ִ� ������ ��ġ
	// rightSlotNum : right �������� �ִ� ������ �ε���
	// return : ���� ����
	bool SwapItem(shared_ptr<Item> leftItem, Slot_Type leftSlotType, int leftSlotNum, shared_ptr<Item> rightItem, Slot_Type rightSlotType, int rightSlotNum);
	bool CanSwap(shared_ptr<Item> leftItem, Slot_Type leftSlotType, shared_ptr<Item> rightItem, Slot_Type rightSlotType);
	bool CanSwap(Item_Type leftItemType, Slot_Type leftSlotType, Item_Type bItemType, Slot_Type rightSlotType);

private:
	// ���������� ������ AddOrEquipItem �Լ�
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

	vector<shared_ptr<Weapon>> _weaponSlot; // ���� ����
	vector<shared_ptr<Accessory>> _accessorySlot; // �Ǽ��縮 ����
	vector<shared_ptr<Item>> _itemSlot; // ������ ����
};

