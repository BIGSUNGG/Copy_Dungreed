#pragma once
class UI_WeaponSlot : public UI
{
public:
	UI_WeaponSlot();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;

protected:

	shared_ptr<Object> _weaponSlotBase1; // ���� ���� ���̽� ù��° �̹���
	shared_ptr<Object> _weaponSlotBase2; // ���� ���� ���̽� �ι�° �̹���
	shared_ptr<Quad> _curWeapon; // ���� ���� �̹���

	shared_ptr<RenderTarget> _weaponSkillRtv;
	shared_ptr<Quad> _weaponSkillBase; 
	shared_ptr<Quad> _weaponSkillIcon; // ���� ���� ��ų ������
	shared_ptr<Quad> _weaponSkillCoolTime; // ���� ���� ��ų ��Ÿ�� �̹���

};

