#include "framework.h"
#include "UI_WeaponSlot.h"

UI_WeaponSlot::UI_WeaponSlot()
	: UI()
{
	_uiType = UI::WEAPON_SLOT;

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

	if (_curWeapon->GetImageFile() != INVENTORY->GetCurWeapon()->GetObjectTexture()->GetImageFile())
	{
		_curWeapon = make_shared<Quad>(INVENTORY->GetCurWeapon()->GetObjectTexture()->GetImageFile());
		_curWeapon->GetTransform()->GetPos() = _weaponSlot1->GetSpawnPos();
		switch (INVENTORY->GetCurWeapon()->GetWeaponType())
		{
		case Weapon::MELEE:
			_curWeapon->GetTransform()->GetAngle() = (1.5f * PI);
			break;
		case Weapon::GUN:
			break;
		case Weapon::SUB:
			break;
		default:
			break;
		}
		_curWeapon->Update();
	}
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
}
