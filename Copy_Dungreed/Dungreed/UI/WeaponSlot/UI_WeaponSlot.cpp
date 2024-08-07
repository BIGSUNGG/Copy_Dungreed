#include "framework.h"
#include "UI_WeaponSlot.h"

UI_WeaponSlot::UI_WeaponSlot()
	: UI()
{
	_weaponSlot1 = make_shared<Object>();
	_weaponSlot1->SetTexture(make_shared<Quad>(L"Resource/Ui/WeaponSlot/WeaponSlot_1.png"));
	_weaponSlot1->GetObjectTexture()->SetRight(WIN_WIDTH - 25);
	_weaponSlot1->GetObjectTexture()->SetBottom(25);
	_weaponSlot1->SetSpawnPos(_weaponSlot1->GetPos());

	_weaponSlot2 = make_shared<Object>();
	_weaponSlot2->SetTexture(make_shared<Quad>(L"Resource/Ui/WeaponSlot/WeaponSlot_2.png"));
	_weaponSlot2->GetObjectTexture()->SetRight(WIN_WIDTH - 10);
	_weaponSlot2->GetObjectTexture()->SetBottom(40);
	_weaponSlot2->SetSpawnPos(_weaponSlot2->GetPos());

	_curWeapon = make_shared<Quad>(L"EMPTY",Vector2(0,0));

	_weaponSkillRtv = make_shared<RenderTarget>(WIN_WIDTH, WIN_HEIGHT);
	float color[4] = { 0,0,0,0.4f };
	_weaponSkillRtv->SetColor(color);


	_weaponSkillBase = make_shared<Quad>(L"Resource/Ui/WeaponSlot/Weapon_Skill.png");
	_weaponSkillBase->GetTransform()->GetPos().y = _weaponSlot1->GetSpawnPos().y;
	_weaponSkillBase->GetTransform()->GetPos().x = _weaponSlot1->GetSpawnPos().x - 325.f;
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
		_weaponSlot1->SetPos(_weaponSlot1->GetSpawnPos());
		_weaponSlot2->SetPos(_weaponSlot2->GetSpawnPos());
	}
	else
	{
		_weaponSlot1->SetPos(_weaponSlot2->GetSpawnPos());
		_weaponSlot2->SetPos(_weaponSlot1->GetSpawnPos());
	}
	_weaponSlot1->Update();

	_weaponSlot2->Update();

	if (INVENTORY->GetCurWeapon() != nullptr)
	{
		if (_curWeapon->GetImageFile() != INVENTORY->GetCurWeapon()->GetIconTexture()->GetImageFile())
		{
			_curWeapon = make_shared<Quad>(INVENTORY->GetCurWeapon()->GetIconTexture()->GetImageFile());
			_curWeapon->GetTransform()->GetPos() = _weaponSlot1->GetSpawnPos();
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
		_curWeapon->GetTransform()->GetPos() = _weaponSlot1->GetSpawnPos();
		_curWeapon->Update();
	}

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
		_weaponSlot2->Render();
		_weaponSlot1->Render();
	}
	else
	{
		_weaponSlot1->Render();
		_weaponSlot2->Render();
	}

	_curWeapon->Render();

	if (INVENTORY->GetCurWeapon() != nullptr && INVENTORY->GetCurWeapon()->GetSkillHuiTexture() != nullptr)
	{
		_weaponSkillBase->Render();
		_weaponSkillIcon->Render();
		_weaponSkillCoolTime->Render();
	}

}
