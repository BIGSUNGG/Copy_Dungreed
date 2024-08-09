#pragma once
class UI_WeaponSlot : public UI
{
public:
	UI_WeaponSlot();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;

protected:

	shared_ptr<Object> _weaponSlotBase1; // 무기 슬롯 베이스 첫번째 이미지
	shared_ptr<Object> _weaponSlotBase2; // 무기 슬롯 베이스 두번째 이미지
	shared_ptr<Quad> _curWeapon; // 현재 무기 이미지

	shared_ptr<RenderTarget> _weaponSkillRtv;
	shared_ptr<Quad> _weaponSkillBase; 
	shared_ptr<Quad> _weaponSkillIcon; // 현재 무기 스킬 아이콘
	shared_ptr<Quad> _weaponSkillCoolTime; // 현재 무기 스킬 쿨타임 이미지

};

