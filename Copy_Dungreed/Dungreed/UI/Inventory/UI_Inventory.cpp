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

	// 무기 슬롯
	for (int i = 0; i < 2; i++)
	{
		auto slot = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Inventory/WeaponSlot.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Inventory/WeaponSlot_Hover.png");
		quad->SetLeft(_curSlot[i]->Left() + 18);
		quad->SetBottom(_curSlot[i]->Bottom() + 18);
		slot->SetTexture(quad);
		slot->SetHoverTexture(hoverQuad);

		// 선택한 아이템 슬롯 설정
		{
			function<void()> func = [&, i]() {
				_selected = true;
				_selectedItem = INVENTORY->GetWeaponSlot()[i];
				_selectedItemImage = make_shared<Quad>(_weapons[i]->GetImageFile());
				_selectedSlotType = Slot_Type::WEAPON_SLOT;
				_selectedSlotNum = i;

				if (_selectedItem == nullptr)
					return;

				shared_ptr<Weapon> weapon = dynamic_pointer_cast<Weapon>(_selectedItem);
				switch (weapon->GetWeaponType())
				{
				case Weapon::MELEE:
					_selectedItemImage->GetTransform()->GetAngle() = (1.5f * PI);
					break;
				case Weapon::GUN:
					break;
				default:
					break;
				}
				};
			slot->SetKeyDownEvent(func);
		}

		// 마우스가 올라가 있는 슬롯 설정
		{
			function<void()> func = [&, i]() {
				_hovered = true;
				_hoveredItem = INVENTORY->GetWeaponSlot()[i];
				_hoveredSlotType = Slot_Type::WEAPON_SLOT;
				_hoveredSlotNum = i;

				};
			slot->SetHoverStartEvent(func);
		}

		// 마우스가 올라가 있는 슬롯 초기화
		{
			function<void()> func = [&, i]() {
				_hovered = false;
				_hoveredItem = nullptr;
				_hoveredSlotType = Slot_Type::NONE;
				_hoveredSlotNum = 0;

				};
			slot->SetHoverEndEvent(func);
		}

		_weaponSlot.emplace_back(slot);
	}
	
	// 보조 무기 슬롯
	for (int i = 0; i < 2; i++)
	{
		auto slot = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Inventory/SubWeaponSlot.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Inventory/SubWeaponSlot_Hover.png");
		quad->SetLeft(_curSlot[i]->Left() + 150);
		quad->SetBottom(_curSlot[i]->Bottom() + 18);
		slot->SetTexture(quad);
		slot->SetHoverTexture(hoverQuad);

		// 선택한 아이템 슬롯 설정
		{
			function<void()> func = [&, i]() {
				_selected = true;
				_selectedItem = nullptr;
				_selectedItemImage = nullptr;
				_selectedSlotType = Slot_Type::SUB_WEAPON_SLOT;
				_selectedSlotNum = i;
				};
			slot->SetKeyDownEvent(func);
		}

		// 마우스가 올라가 있는 슬롯 설정
		{
			function<void()> func = [&, i]() {
				_hovered = true;
				_hoveredItem = nullptr;
				_hoveredSlotType = Slot_Type::SUB_WEAPON_SLOT;
				_hoveredSlotNum = i;

				};
			slot->SetHoverStartEvent(func);
		}

		// 마우스가 올라가 있는 슬롯 초기화
		{
			function<void()> func = [&, i]() {
				_hovered = false;
				_hoveredItem = nullptr;
				_hoveredSlotType = Slot_Type::NONE;
				_hoveredSlotNum = 0;

				};
			slot->SetHoverEndEvent(func);
		}

		_subWeaponSlot.emplace_back(slot);
	}

	// 악세사리 슬롯
	for (int i = 0; i < 4; i++)
	{
		auto slot = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Inventory/AccessorySlot.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Inventory/AccessorySlot_Hover.png");
		quad->SetLeft(_invenBase->Left() + 130 + (129 * i));
		quad->SetBottom(609);
		slot->SetTexture(quad);
		slot->SetHoverTexture(hoverQuad);

		// 선택한 아이템 슬롯 설정
		{
			function<void()> func = [&, i]() {
				_selected = true;
				_selectedItem = INVENTORY->GetAccessorySlot()[i];
				_selectedItemImage = make_shared<Quad>(_accessories[i]->GetImageFile());
				_selectedSlotType = Slot_Type::ACCESSORY_SLOT;
				_selectedSlotNum = i;
				};
			slot->SetKeyDownEvent(func);
		}

		// 마우스가 올라가 있는 슬롯 설정
		{
			function<void()> func = [&, i]() {
				_hovered = true;
				_hoveredItem = INVENTORY->GetAccessorySlot()[i];
				_hoveredSlotType = Slot_Type::ACCESSORY_SLOT;
				_hoveredSlotNum = i;

				};
			slot->SetHoverStartEvent(func);
		}

		// 마우스가 올라가 있는 슬롯 초기화
		{
			function<void()> func = [&, i]() {
				_hovered = false;
				_hoveredItem = nullptr;
				_hoveredSlotType = Slot_Type::NONE;
				_hoveredSlotNum = 0;

				};
			slot->SetHoverEndEvent(func);
		}

		_accessorySlot.emplace_back(slot);
	}

	// 아이템 슬롯
	for (int j = 0; j < 3; j++)
	{
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

				// 선택한 아이템 슬롯 설정
				{
					function<void()> func = [&, index]() {
						_selected = true;
						_selectedItemImage = make_shared<Quad>(_items[index]->GetImageFile());
						_selectedSlotType = Slot_Type::ITEM_SLOT;
						_selectedSlotNum = index;
						_selectedItem = INVENTORY->GetItemSlot()[index];

						if (INVENTORY->GetItemSlot()[index] != nullptr)
						{
							switch (INVENTORY->GetItemSlot()[index]->GetItemType())
							{
							case Item_Type::WEAPON:
							{
								shared_ptr<Weapon> weapon = dynamic_pointer_cast<Weapon>(INVENTORY->GetItemSlot()[index]);
								switch (weapon->GetWeaponType())
								{
								case Weapon::MELEE:
									_selectedItemImage->GetTransform()->GetAngle() = (1.5f * PI);
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
						};

					slot->SetKeyDownEvent(func);
				}

				// 마우스가 올라가 있는 슬롯 설정
				{
					function<void()> func = [&, index]() {
						_hovered = true;
						_hoveredItem = INVENTORY->GetItemSlot()[index];
						_hoveredSlotType = Slot_Type::ITEM_SLOT;
						_hoveredSlotNum = index;

						};
					slot->SetHoverStartEvent(func);
				}

				// 마우스가 올라가 있는 슬롯 초기화
				{
					function<void()> func = [&, index]() {
						_hovered = false;
						_hoveredItem = nullptr;
						_hoveredSlotType = Slot_Type::NONE;
						_hoveredSlotNum = 0;

						};
					slot->SetHoverEndEvent(func);
				}

				_itemSlot.emplace_back(slot);
			}
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

	_goldText = make_shared<UI_Text>();
	_goldText->SetTextSize(65.0f);
	_goldText->SetTextStatus(UI_Text::Text_Status::RIGHT);
	_goldText->SetPos(Vector2(WIN_WIDTH - 110, 70));
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

	if (_selectedItemImage != nullptr)
		_selectedItemImage->Update();

	std::wstring coinText;
	coinText += to_wstring(INVENTORY->GetCurGold());
	_goldText->SetText(coinText);

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

	if (_selected == true && _selectedItemImage != nullptr)
		_selectedItemImage->Render();

	_goldText->Render();
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
				case Item_Type::WEAPON:
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
	// 현재 선택한 아이템 위치를 마우스와 같게함
	if (KEY_PRESS(VK_LBUTTON))
	{
		if (_selectedItemImage == nullptr)
			return;

		_selectedItemImage->GetTransform()->GetPos() = MOUSE_POS;
	}
	// 현재 선택한 아이템을 마우스 위에 있는 인벤토리에 넣기
	else if (KEY_UP(VK_LBUTTON))
	{
		if (_selected == false || _selectedItem == nullptr)
			return;

		if (_hovered) // 교체할 슬롯이 있다면
			bool swapSuccess = INVENTORY->GetInventory()->SwapItem(_selectedItem, _selectedSlotType, _selectedSlotNum, _hoveredItem, _hoveredSlotType, _hoveredSlotNum);

		// 선택한 아이템 정보 초기화
		_selected = false;
		_selectedItem = nullptr;
		_selectedItemImage = nullptr;
		_selectedSlotType = Slot_Type::NONE;
		_selectedSlotNum = 0;
	}
}