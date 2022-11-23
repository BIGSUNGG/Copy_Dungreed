#include "framework.h"
#include "Chest.h"

Chest::Chest(int type, int num)
	: Ect(type, num)
{
	_ectType = Ect::CHEST;
	_movement = make_shared<MovementComponent>(this);
	_interaction = false;
	_render = false;
	_renderOrder = 3.5f;

	MakeRandomItem();	
}

void Chest::Update()
{
	if(_spawn)
		_movement->Update();

	Ect::Update();
}

void Chest::Interaction()
{
	if (!_interaction || _dropItem == nullptr) return;

	_interaction = false;
	_texture->SetImage(_openImage);

	_dropItem->GetPos().x = this->GetPos().x;
	_dropItem->GetObjectTexture()->SetBottom(_texture->Bottom());
	_dropItem->GetMovementComponent()->SetBeforeMove(_dropItem->GetPos());
	_dropItem->GetMovementComponent()->Jump();
	GAME->AddEctObject(_dropItem);
	_dropItem = nullptr;
}

void Chest::SetOwnerMap(shared_ptr<Map> map)
{
	Ect::SetOwnerMap(map);

	map->AddOpenEvent([&]() 
		{
			shared_ptr<Effect> spawn = MAKE_CREATURE_EFFECT(Map::Level::PUBLIC, 1);
			spawn->GetObjectTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();

			if (_reversed)
				spawn->GetObjectTexture()->ReverseToX();

			function<void(pair<int, int> pair)> func = [&](pair<int, int> pair) {
				if (pair.first == BASIC && pair.second == 10)
				{
					_render = true;
					_spawn = true;
				}
				if (pair.first == BASIC && pair.second == 14)
					_interaction = true;
				};
			spawn->GetAnimation()->SetAfterChangeFunc(func);

			GAME->AddEffect(spawn);
		});
}

void Chest::MakeRandomItem()
{
	shared_ptr<Item> randomItem;

	while (randomItem == nullptr)
	{
		char itemType = rand() % 3;
		char itemNum = rand() % 10;

		switch (itemType)
		{
		case Item::WEAPON:
		{
			char weaponType = rand() % 2;
			randomItem = OBJ_MANAGER->GetPlayerWeapon(weaponType, itemNum);
		}
		break;
		case Item::SUB_WEAPON:
			randomItem = OBJ_MANAGER->GetPlayerSubWeapon(itemNum);
			break;
		case Item::ACCESSORY:
			randomItem = OBJ_MANAGER->GetPlayerAccessory(itemNum);
			break;
		case Item::NONE:
			break;
		default:
			break;
		}
	}
	_dropItem = make_shared<DropItem>(randomItem->GetLevel(), randomItem->GetNum());
	_dropItem->SetItem(randomItem);
}

