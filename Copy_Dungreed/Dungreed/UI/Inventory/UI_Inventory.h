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

protected:
	shared_ptr<Quad> _invenBase; // 인벤토리 베이스 텍스쳐
	vector<shared_ptr<Quad>> _curSlot; // 현재 슬롯 텍스쳐
	vector<shared_ptr<UI_Button>> _weaponSlot; 
	vector<shared_ptr<UI_Button>> _subWeaponSlot; 
	vector<shared_ptr<UI_Button>> _accessorySlot;
	vector<shared_ptr<UI_Button>> _itemSlot; 
	shared_ptr<UI_Button> _exitButton;

	vector<shared_ptr<Quad>> _weapons; // 현재 장착중인 무기 텍스쳐
	vector<shared_ptr<Quad>> _accessories; // 현재 장착중인 악세사리 텍스쳐
	vector<shared_ptr<Quad>> _items; // 현재 보유중인 아이템 텍스쳐

	shared_ptr<Quad> _selectedItem; // 마우스로 움직이고 있는 아이템
	Slot_Type _selectedSlotType = Slot_Type::NONE; // 현재 선택한 아이템 슬롯의 타입
	int _selectedSlotNum = 0; // 현재 선택한 아이템 슬롯의 번호

	shared_ptr<UI_Text> _goldText; // 현재 골드 텍스트
};

