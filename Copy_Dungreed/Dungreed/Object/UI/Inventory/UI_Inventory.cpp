#include "framework.h"
#include "UI_Inventory.h"

UI_Inventory::UI_Inventory()
	: UI()
{
	_invenBase = make_shared<Quad>(L"Resource/Ui/Inventory/InventoryBase.png");
	_invenBase->SetRight(WIN_WIDTH);
	_invenBase->GetTransform()->GetPos().y = CENTER.y;

	{
		auto firstSlot = make_shared<Quad>(L"Resource/Ui/Inventory/CurSlot_First.png");
		firstSlot->SetBottom(762);
		firstSlot->SetLeft(_invenBase->Left() + 78);
		_curSlot.emplace_back(firstSlot);

		auto secondSlot = make_shared<Quad>(L"Resource/Ui/Inventory/CurSlot_Second.png");
		secondSlot->SetBottom(762);
		secondSlot->SetLeft(_invenBase->Left() + 402);
		_curSlot.emplace_back(secondSlot);
	}

	for (int i = 0; i < 2; i++)
	{
		auto slot = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Inventory/WeaponSlot.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Inventory/WeaponSlot_Hover.png");
		quad->SetLeft(_curSlot[i]->Left() + 18);
		quad->SetBottom(_curSlot[i]->Bottom() + 18);
		slot->SetTexture(quad);
		slot->SetHoverTexture(hoverQuad);
		_weaponSlots.emplace_back(slot);
	}

	for (int i = 0; i < 2; i++)
	{
		auto slot = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Inventory/SubWeaponSlot.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Inventory/SubWeaponSlot_Hover.png");
		quad->SetLeft(_curSlot[i]->Left() + 150);
		quad->SetBottom(_curSlot[i]->Bottom() + 18);
		slot->SetTexture(quad);
		slot->SetHoverTexture(hoverQuad);
		_weaponSlots.emplace_back(slot);
	}

	for (int i = 0; i < 4; i++)
	{
		auto slot = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Inventory/AccessorieSlot.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Inventory/AccessorieSlot_Hover.png");
		quad->SetLeft(_invenBase->Left() + 130 + (129 * i));
		quad->SetBottom(609);
		slot->SetTexture(quad);
		slot->SetHoverTexture(hoverQuad);
		_accessorieSlots.emplace_back(slot);
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			auto slot = make_shared<UI_Button>();
			auto quad = make_shared<Quad>(L"Resource/Ui/Inventory/BasicSlot.png");
			auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Inventory/BasicSlot_Hover.png");
			quad->SetLeft(_invenBase->Left() + 59 + (132 * i));
			quad->SetBottom(168 + (132 * j));
			slot->SetTexture(quad);
			slot->SetHoverTexture(hoverQuad);
			_accessorieSlots.emplace_back(slot);
		}
	}

	_weapons.resize(2, make_shared<Quad>(L"EMPTY", Vector2(0, 0)));
}

void UI_Inventory::Update()
{
	_invenBase->Update();
	for (auto& slot : _curSlot)
		slot->Update();

	for (auto& slot : _weaponSlots)
		slot->Update();

	for (auto& slot : _accessorieSlots)
		slot->Update();

	for (int i = 0; i < 2; i++)
	{
		if (_weapons[i]->GetImageFile() != INVENTORY->GetWeaponSlot()[i]->GetObjectTexture()->GetImageFile())
		{
			_weapons[i] = make_shared<Quad>(INVENTORY->GetWeaponSlot()[i]->GetObjectTexture()->GetImageFile());
			_weapons[i]->GetTransform()->GetPos() = _weaponSlots[i]->GetPos();
			switch (INVENTORY->GetWeaponSlot()[i]->GetWeaponType())
			{
			case Weapon::MELEE:
				_weapons[i]->GetTransform()->GetAngle() = (1.5f * PI);
				break;
			case Weapon::GUN:
				break;
			case Weapon::SUB:
				break;
			default:
				break;
			}
			_weapons[i]->Update();
		}
	}
}

void UI_Inventory::Render()
{
	_invenBase->Render();
	_curSlot[INVENTORY->GetCurWeaponSlot()]->Render();

	for (auto& slot : _weaponSlots)
		slot->Render();

	for (auto& slot : _accessorieSlots)
		slot->Render();

	for (auto& weapon : _weapons)
		weapon->Render();

	std::wstring coinText;
	coinText += to_wstring(INVENTORY->GetGold());
	RECT coinTextRect =
	{
		WIN_WIDTH - 150 - (_coinTextSize * (coinText.size() - 1) / 2)	,WIN_HEIGHT - 104,
		WIN_WIDTH, WIN_HEIGHT
	};

	DirectWrite::GetInstance()->RenderText(coinText, coinTextRect, _coinTextSize);
}
