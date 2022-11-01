#pragma once
class UI_Inventory : public UI
{
public:
	UI_Inventory();

	virtual void Update() override;
	virtual void Render() override;

	virtual void FindTexture();
	virtual void MouseEvenet();

protected:
	shared_ptr<Quad> _invenBase;
	vector<shared_ptr<Quad>> _curSlot;
	vector<shared_ptr<UI_Button>> _weaponSlot;
	vector<shared_ptr<UI_Button>> _subWeaponSlot;
	vector<shared_ptr<UI_Button>> _accessorySlot;
	vector<shared_ptr<UI_Button>> _itemSlot;
	shared_ptr<UI_Button> _exitButton;

	vector<shared_ptr<Quad>> _weapons;
	vector<shared_ptr<Quad>> _accessories;
	vector<shared_ptr<Quad>> _items;

	shared_ptr<Quad> _selectedItem;
	shared_ptr<UI_Text> _coinText;

	int _type = 0;
	int _num = 0;
};

