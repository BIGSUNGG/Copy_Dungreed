#pragma once
class UI_Inventory : public UI
{
public:
	UI_Inventory();

	virtual void Update() override;
	virtual void Render() override;

private:
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

