#pragma once
class UI_Inventory : public UI
{
public:
	UI_Inventory();

	virtual void Update() override;
	virtual void Render() override;

protected:
	const float _coinTextSize = 65.0f;

	shared_ptr<Quad> _invenBase;
	vector<shared_ptr<Quad>> _curSlot;
	vector<shared_ptr<UI_Button>> _weaponSlots;
	vector<shared_ptr<UI_Button>> _accessorieSlots;
	vector<shared_ptr<UI_Button>> _basicSlots;

	vector<shared_ptr<Quad>> _weapons;
};

