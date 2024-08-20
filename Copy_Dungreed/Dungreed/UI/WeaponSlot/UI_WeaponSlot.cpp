#include "framework.h"
#include "UI_WeaponSlot.h"

UI_WeaponSlot::UI_WeaponSlot()
	: UI()
{
	_weaponSlotBase1 = make_shared<Object>();
	_weaponSlotBase1->SetTexture(make_shared<Quad>(L"Resource/Ui/WeaponSlot/WeaponSlot_1.png"));
	_weaponSlotBase1->GetObjectTexture()->SetRight(WIN_WIDTH - 25);
	_weaponSlotBase1->GetObjectTexture()->SetBottom(25);
	_weaponSlotBase1->SetSpawnPos(_weaponSlotBase1->GetPos());

	_weaponSlotBase2 = make_shared<Object>();
	_weaponSlotBase2->SetTexture(make_shared<Quad>(L"Resource/Ui/WeaponSlot/WeaponSlot_2.png"));
	_weaponSlotBase2->GetObjectTexture()->SetRight(WIN_WIDTH - 10);
	_weaponSlotBase2->GetObjectTexture()->SetBottom(40);
	_weaponSlotBase2->SetSpawnPos(_weaponSlotBase2->GetPos());

	_curWeapon = make_shared<Quad>(L"EMPTY",Vector2(0,0));

	_weaponSkillRtv = make_shared<RenderTarget>(WIN_WIDTH, WIN_HEIGHT);
	float color[4] = { 0,0,0,0.4f };
	_weaponSkillRtv->SetColor(color);


	_weaponSkillBase = make_shared<Quad>(L"Resource/Ui/WeaponSlot/Weapon_Skill.png");
	_weaponSkillBase->GetTransform()->GetPos().y = _weaponSlotBase1->GetSpawnPos().y;
	_weaponSkillBase->GetTransform()->GetPos().x = _weaponSlotBase1->GetSpawnPos().x - 325.f;
	_weaponSkillBase->Update();

	_weaponSkillIcon = make_shared<Quad>(L"EMPTY", Vector2(0, 0));
	_weaponSkillIcon->GetTransform()->GetPos() = _weaponSkillBase->GetTransform()->GetPos();
	_weaponSkillIcon->Update();

	_weaponSkillCoolTime = make_shared<Quad>(L"Skill_Cool_Time", Vector2(_weaponSkillBase->GetSize()));
	shared_ptr<Texture> texture = Texture::Add(L"MiniMap_Base_Texture", _weaponSkillRtv->GetSRV());
	_weaponSkillCoolTime->SetImage(texture);
	_weaponSkillCoolTime->GetTransform()->GetPos() = _weaponSkillBase->GetTransform()->GetPos();
	_weaponSkillCoolTime->Update();
}

void UI_WeaponSlot::Update()
{
	if (INVENTORY->GetCurWeaponSlot() == 0)
	{
		_weaponSlotBase1->SetPos(_weaponSlotBase1->GetSpawnPos());
		_weaponSlotBase2->SetPos(_weaponSlotBase2->GetSpawnPos());
	}
	else
	{
		_weaponSlotBase1->SetPos(_weaponSlotBase2->GetSpawnPos());
		_weaponSlotBase2->SetPos(_weaponSlotBase1->GetSpawnPos());
	}
	_weaponSlotBase1->Update();
	_weaponSlotBase2->Update();

	// 현재 무기 이미지 설정
	if (INVENTORY->GetCurWeapon() != nullptr)
	{
		if (_curWeapon->GetImageFile() != INVENTORY->GetCurWeapon()->GetIconTexture()->GetImageFile())
		{
			_curWeapon = make_shared<Quad>(INVENTORY->GetCurWeapon()->GetIconTexture()->GetImageFile());
			_curWeapon->GetTransform()->GetPos() = _weaponSlotBase1->GetSpawnPos();
			switch (INVENTORY->GetCurWeapon()->GetWeaponType())
			{
			case Weapon::MELEE:
				_curWeapon->GetTransform()->GetAngle() = (1.5f * PI);
				break;
			case Weapon::GUN:
				break;
			default:
				break;
			}
			_curWeapon->Update();
		}
	}
	else
	{
		_curWeapon = make_shared<Quad>(L"EMPTY", (Vector2(0, 0)));
		_curWeapon->GetTransform()->GetPos() = _weaponSlotBase1->GetSpawnPos();
		_curWeapon->Update();
	}

	// 현재 스킬 이미지 설정
	if (INVENTORY->GetCurWeapon() != nullptr && INVENTORY->GetCurWeapon()->GetSkillHuiTexture() != nullptr)
	{
		if (_weaponSkillIcon->GetImageFile() != INVENTORY->GetCurWeapon()->GetSkillHuiTexture()->GetImageFile())
		{
			_weaponSkillIcon->SetImage(INVENTORY->GetCurWeapon()->GetSkillHuiTexture()->GetImageFile());
			_weaponSkillIcon->Refresh();
			_weaponSkillIcon->Update();
		}
		_weaponSkillCoolTime->GetTransform()->GetScale().x = abs(INVENTORY->GetCurWeapon()->GetSkillCoolTimeRatio() - 1.f);
		_weaponSkillCoolTime->SetLeft(_weaponSkillBase->Left());
		_weaponSkillCoolTime->Update();
	}

}

void UI_WeaponSlot::PreRender()
{
	_weaponSkillRtv->Set();
}

void UI_WeaponSlot::Render()
{
	if (INVENTORY->GetCurWeaponSlot() == 0)
	{
		_weaponSlotBase2->Render();
		_weaponSlotBase1->Render();
	}
	else
	{
		_weaponSlotBase1->Render(); 
		_weaponSlotBase2->Render();
	}
	

	_curWeapon->Render();

	if (INVENTORY->GetCurWeapon() != nullptr && INVENTORY->GetCurWeapon()->GetSkillHuiTexture() != nullptr)
	{
		_weaponSkillBase->Render();
		_weaponSkillIcon->Render();
		_weaponSkillCoolTime->Render();
	}

}
