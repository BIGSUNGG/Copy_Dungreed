#pragma once
class UI_WeaponSlot : public UI
{
public:
	UI_WeaponSlot();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;

protected:

	shared_ptr<Object> _weaponSlot1;
	shared_ptr<Object> _weaponSlot2;
	shared_ptr<Quad> _curWeapon;

	shared_ptr<RenderTarget> _weaponSkillRtv;
	shared_ptr<Quad> _weaponSkillBase;
	shared_ptr<Quad> _weaponSkillIcon;
	shared_ptr<Quad> _weaponSkillCoolTime;

};

