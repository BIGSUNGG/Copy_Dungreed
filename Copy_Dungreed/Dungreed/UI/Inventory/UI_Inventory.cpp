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
		function<void()> func = [&, i]() {
			_selectedItem = make_shared<Quad>(_weapons[i]->GetImageFile());

			shared_ptr<Weapon> weapon = dynamic_pointer_cast<Weapon>(INVENTORY->GetWeaponSlot()[i]);
			switch (weapon->GetWeaponType())
			{
			case Weapon::MELEE:
				_selectedItem->GetTransform()->GetAngle() = (1.5f * PI);
				break;
			case Weapon::GUN:
				break;
			default:
				break;
			}

			_type = 0;
			_num = i;
			return;
		};
		slot->SetKeyDownEvent(func);
		_weaponSlot.emplace_back(slot);
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
		function<void()> func = [&, i]() {
		};
		slot->SetKeyDownEvent(func);
		_subWeaponSlot.emplace_back(slot);
	}

	for (int i = 0; i < 4; i++)
	{
		auto slot = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Inventory/AccessorySlot.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Inventory/AccessorySlot_Hover.png");
		quad->SetLeft(_invenBase->Left() + 130 + (129 * i));
		quad->SetBottom(609);
		slot->SetTexture(quad);
		slot->SetHoverTexture(hoverQuad);
		function<void()> func = [&, i]() {
			_selectedItem = make_shared<Quad>(_accessories[i]->GetImageFile());
			_type = 1;
			_num = i;
			return;
		};
		slot->SetKeyDownEvent(func);
		_accessorySlot.emplace_back(slot);
	}

	for (int j = 0; j < 3; j++)
		for (int i = 0; i < 5; i++)
		{
			{
				auto slot = make_shared<UI_Button>();
				auto quad = make_shared<Quad>(L"Resource/Ui/Inventory/BasicSlot.png");
				auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Inventory/BasicSlot_Hover.png");
				quad->SetLeft(_invenBase->Left() + 59 + (132 * i));
				quad->SetBottom(432 - (132 * j));
				slot->SetTexture(quad);
				slot->SetHoverTexture(hoverQuad);
				
				int index = (j * 5) + i;
				function<void()> func = [&, index]() {
					_selectedItem = make_shared<Quad>(_items[index]->GetImageFile());

					if (INVENTORY->GetItemSlot()[index] != nullptr)
					{
						switch (INVENTORY->GetItemSlot()[index]->GetItemType())
						{
						case Item::WEAPON:
						{
							shared_ptr<Weapon> weapon = dynamic_pointer_cast<Weapon>(INVENTORY->GetItemSlot()[index]);
							switch (weapon->GetWeaponType())
							{
							case Weapon::MELEE:
								_selectedItem->GetTransform()->GetAngle() = (1.5f * PI);
								break;
							case Weapon::GUN:
								break;
							default:
								break;
							}
						}
						break;
						default:
							break;
						}
					}

					_type = 2;
					_num = index;
					return;
				};
				slot->SetKeyDownEvent(func);
				_itemSlot.emplace_back(slot);
			}
		}

	{
		_exitButton = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Inventory/Exit.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Inventory/Exit_Hover.png");
		quad->SetRight(_invenBase->Left());
		quad->SetTop(WIN_HEIGHT - 9);
		_exitButton->SetTexture(quad);
		_exitButton->SetHoverTexture(hoverQuad);
		function<void()> func = []() { UI_MANAGER->SetState(UIManager::UI_State::NOMAL); };
		_exitButton->SetKeyUpEvent(func);
	}

	_weapons.resize(2, make_shared<Quad>(L"EMPTY", Vector2(0, 0)));
	_accessories.resize(4, make_shared<Quad>(L"EMPTY", Vector2(0, 0)));
	_items.resize(15, make_shared<Quad>(L"EMPTY", Vector2(0, 0)));

	_coinText = make_shared<UI_Text>();
	_coinText->SetTextSize(65.0f);
	_coinText->SetTextStatus(UI_Text::Text_Status::RIGHT);
	_coinText->SetPos(Vector2(WIN_WIDTH - 110, 70));
}

void UI_Inventory::Update()
{
	FindTexture();

	_invenBase->Update();
	_exitButton->Update();

	for (auto& slot : _curSlot)
		slot->Update();

	for (auto& slot : _weaponSlot)
		slot->Update();

	for (auto& slot : _subWeaponSlot)
		slot->Update();

	for (auto& slot : _accessorySlot)
		slot->Update();

	for (auto& slot : _itemSlot)
		slot->Update();

	for (auto& weapon : _weapons)
		weapon->Update();

	for (auto& accessory : _accessories)
		accessory->Update();

	for (auto& item : _items)
		item->Update();

	if (_selectedItem != nullptr)
		_selectedItem->Update();

	std::wstring coinText;
	coinText += to_wstring(INVENTORY->GetCurGold());
	_coinText->SetText(coinText);

	MouseEvenet();
}

void UI_Inventory::Render()
{
	_invenBase->Render();
	_exitButton->Render();
	_curSlot[INVENTORY->GetCurWeaponSlot()]->Render();

	for (auto& slot : _weaponSlot)
		slot->Render();

	for (auto& slot : _subWeaponSlot)
		slot->Render();

	for (auto& slot : _accessorySlot)
		slot->Render();

	for (auto& slot : _itemSlot)
		slot->Render();

	for (auto& weapon : _weapons)
		weapon->Render();

	for (auto& accessory : _accessories)
		accessory->Render();

	for (auto& item : _items)
		item->Render();

	if (_selectedItem != nullptr)
		_selectedItem->Render();

	_coinText->Render();
}

void UI_Inventory::FindTexture()
{
	// 무기 슬롯 이미지 찾기
	for (int i = 0; i < 2; i++)
	{
		if (INVENTORY->GetWeaponSlot()[i] != nullptr)
		{
			if (_weapons[i]->GetImageFile() != INVENTORY->GetWeaponSlot()[i]->GetIconTexture()->GetImageFile())
			{
				_weapons[i] = make_shared<Quad>(INVENTORY->GetWeaponSlot()[i]->GetIconTexture()->GetImageFile());
				_weapons[i]->GetTransform()->GetPos() = _weaponSlot[i]->GetPos();
				switch (INVENTORY->GetWeaponSlot()[i]->GetWeaponType())
				{
				case Weapon::MELEE:
					_weapons[i]->GetTransform()->GetAngle() = (1.5f * PI);
					break;
				case Weapon::GUN:
					break;
				default:
					break;
				}
			}
		}
		else
		{
			_weapons[i] = make_shared<Quad>(L"EMPTY", Vector2(0, 0));
			_weapons[i]->GetTransform()->GetPos() = _weaponSlot[i]->GetPos();
		}
	}
	// 악세사리 슬롯 이미지 찾기
	for (int i = 0; i < 4; i++)
	{
		if (INVENTORY->GetAccessorySlot()[i] != nullptr)
		{
			if (_accessories[i]->GetImageFile() != INVENTORY->GetAccessorySlot()[i]->GetIconTexture()->GetImageFile())
			{
				_accessories[i] = make_shared<Quad>(INVENTORY->GetAccessorySlot()[i]->GetIconTexture()->GetImageFile());
				_accessories[i]->GetTransform()->GetPos() = _accessorySlot[i]->GetPos();
			}
		}
		else
		{
			_accessories[i] = make_shared<Quad>(L"EMPTY", Vector2(0, 0));
			_accessories[i]->GetTransform()->GetPos() = _accessorySlot[i]->GetPos();
		}
	}

	// 아이템 슬롯 이미지 찾기
	for (int i = 0; i < 15; i++)
	{
		if (INVENTORY->GetItemSlot()[i] != nullptr)
		{
			if (_items[i]->GetImageFile() != INVENTORY->GetItemSlot()[i]->GetIconTexture()->GetImageFile())
			{
				_items[i] = make_shared<Quad>(INVENTORY->GetItemSlot()[i]->GetIconTexture()->GetImageFile());
				_items[i]->GetTransform()->GetPos() = _itemSlot[i]->GetPos();

				switch (INVENTORY->GetItemSlot()[i]->GetItemType())
				{
				case Item::WEAPON:
				{
					shared_ptr<Weapon> weapon = dynamic_pointer_cast<Weapon>(INVENTORY->GetItemSlot()[i]);
					switch (weapon->GetWeaponType())
					{
					case Weapon::MELEE:
						_items[i]->GetTransform()->GetAngle() = (1.5f * PI);
						break;
					case Weapon::GUN:
						break;
					default:
						break;
					}
				}
					break;
				default:
					break;
				}
			}
		}
		else
		{
			_items[i] = make_shared<Quad>(L"EMPTY", Vector2(0, 0));
			_items[i]->GetTransform()->GetPos() = _itemSlot[i]->GetPos();
		}
	}
}

void UI_Inventory::MouseEvenet()
{
	if (KEY_PRESS(VK_LBUTTON))
	{
		if (_selectedItem == nullptr)
			return;

		_selectedItem->GetTransform()->GetPos() = MOUSE_POS;
	}
	else if (KEY_UP(VK_LBUTTON))
	{
		if (_selectedItem == nullptr)
			return;

		bool swap = false;
		shared_ptr<Item> selected;
		shared_ptr<Item> swapItem;
		if (_type == 0)
		{
			_selectedItem->GetTransform()->GetPos() = _weaponSlot[_num]->GetPos();
			selected = INVENTORY->GetWeaponSlot()[_num];
		}
		else if (_type == 1)
		{
			_selectedItem->GetTransform()->GetPos() = _accessorySlot[_num]->GetPos();
			selected = INVENTORY->GetAccessorySlot()[_num];
		}
		else if (_type == 2)
		{
			_selectedItem->GetTransform()->GetPos() = _itemSlot[_num]->GetPos();
			selected = INVENTORY->GetItemSlot()[_num];
		}

		if (selected == nullptr)
			return;

		for (int i = 0; i < 2; i++)
		{
			if (_weaponSlot[i]->GetHover())
			{
				if (selected->GetItemType() == Item::WEAPON)
				{
					swapItem = INVENTORY->GetWeaponSlot()[i];
					INVENTORY->GetWeaponSlot()[i] = dynamic_pointer_cast<Weapon>(selected);
					swap = true;
				}
			}
		}

		for (int i = 0; i < _accessorySlot.size(); i++)
		{
			if (_accessorySlot[i]->GetHover())
			{
				if (selected->GetItemType() == Item::ACCESSORY)
				{
					swapItem = INVENTORY->GetAccessorySlot()[i];
					INVENTORY->GetAccessorySlot()[i] = dynamic_pointer_cast<Accessory>(selected);
					swap = true;
				}
			}
		}

		for (int i = 0; i < _itemSlot.size(); i++)
		{
			if (_itemSlot[i]->GetHover())
			{
				swapItem = INVENTORY->GetItemSlot()[i];
				INVENTORY->GetItemSlot()[i] = dynamic_pointer_cast<Item>(selected);
				swap = true;
			}
		}

		_selectedItem = nullptr;
		if (swap)
		{
			if (_type == 0)
			{
				INVENTORY->GetWeaponSlot()[_num] = dynamic_pointer_cast<Weapon>(swapItem);
			}
			else if (_type == 1)
			{
				INVENTORY->GetAccessorySlot()[_num] = dynamic_pointer_cast<Accessory>(swapItem);
			}
			else if (_type == 2)
			{
				INVENTORY->GetItemSlot()[_num] = swapItem;
			}
		}
	}
}
