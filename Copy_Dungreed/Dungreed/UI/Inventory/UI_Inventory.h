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

	shared_ptr<Quad> _selectedItem; // ���콺�� �����̰� �ִ� ������
	Slot_Type _selectedSlotType = Slot_Type::NONE; // ���� ������ ������ ������ Ÿ��
	int _selectedSlotNum = 0; // ���� ������ ������ ������ ��ȣ

	shared_ptr<UI_Text> _goldText; // ���� ��� �ؽ�Ʈ
};

