#pragma once
class UI_Inventory : public UI
{
private:
	enum class Slot_Type
	{
		NONE,
		WEAPON_SLOT,
		SUB_WEAPON_SLOT,
		ACCESSORY_SLOT,
		ITEM_SLOT
	};

public:
	UI_Inventory();

	virtual void Update() override;
	virtual void Render() override;

	virtual void FindTexture();
	virtual void MouseEvenet();

private:
	bool SwapItem(shared_ptr<Item> aItem, Slot_Type aSlotType, int aSlotNum, shared_ptr<Item> bItem, Slot_Type bSlotType, int bSlotNum);
	bool CanSwap(shared_ptr<Item> aItem, Slot_Type aSlotType, shared_ptr<Item> bItem, Slot_Type bSlotType);
	bool CanSwap(Item::Item_Type aItemType, Slot_Type aSlotType, Item::Item_Type bItemType, Slot_Type bSlotType);

protected:
	shared_ptr<Quad> _invenBase; // �κ��丮 ���̽� �ؽ���
	vector<shared_ptr<Quad>> _curSlot; // ���� ���� �ؽ���
	vector<shared_ptr<UI_Button>> _weaponSlot; 
	vector<shared_ptr<UI_Button>> _subWeaponSlot; 
	vector<shared_ptr<UI_Button>> _accessorySlot;
	vector<shared_ptr<UI_Button>> _itemSlot; 
	shared_ptr<UI_Button> _exitButton;

	vector<shared_ptr<Quad>> _weapons; // ���� �������� ���� �ؽ���
	vector<shared_ptr<Quad>> _accessories; // ���� �������� �Ǽ��縮 �ؽ���
	vector<shared_ptr<Quad>> _items; // ���� �������� ������ �ؽ���

	shared_ptr<UI_Text> _goldText; // ���� ��� �ؽ�Ʈ

	bool _selected = false;
	shared_ptr<Item> _selectedItem = nullptr;
	shared_ptr<Quad> _selectedItemImage; // ���콺�� �����̰� �ִ� ���� ������ ������
	Slot_Type _selectedSlotType = Slot_Type::NONE; // ���� ������ ������ ������ Ÿ��
	int _selectedSlotNum = 0; // ���� ������ ������ ������ ��ȣ

	bool _hovered = false;
	shared_ptr<Item> _hoveredItem = nullptr;
	Slot_Type _hoveredSlotType = Slot_Type::NONE; // ���� ���콺�� �ö� �ִ� ���� Ÿ��
	int _hoveredSlotNum = 0; // ���� ���콺�� �ö� �ִ� ���� ��ȣ
};

