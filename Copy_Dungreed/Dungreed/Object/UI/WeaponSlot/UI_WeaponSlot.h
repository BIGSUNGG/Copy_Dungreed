#pragma once
class UI_WeaponSlot : public UI
{
public:
	UI_WeaponSlot();

	virtual void Update() override;
	virtual void Render() override;

protected:
	shared_ptr<Object> _weaponSlot1;
	shared_ptr<Object> _weaponSlot2;

};

