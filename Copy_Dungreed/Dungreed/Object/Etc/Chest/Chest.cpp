#include "framework.h"
#include "Chest.h"

Chest::Chest(int type, int num)
	: Etc(type, num)
{
	_etcType = Etc::CHEST;
	_movement = make_shared<MovementComponent>(this);
	_interaction = false;
	_render = false;

	MakeRandomItem();	
}

void Chest::Update()
{
	if(_spawn)
		_movement->Update();

	Etc::Update();
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
	GAME->AddEtcObject(_dropItem);
	_dropItem = nullptr;
}

void Chest::SetOwnerMap(shared_ptr<StageMap> map)
{
	Etc::SetOwnerMap(map);

	map->AddOpenEvent([&]() 
		{
			shared_ptr<Effect> spawn = MAKE_CREATURE_EFFECT(StageMap::Level::PUBLIC, 1);
			spawn->GetObjectTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();

			if (_reverseTexture)
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

		switch (static_cast<Item_Type>(itemType))
		{
		case Item_Type::WEAPON:
		{
			char weaponType = rand() % 2;
			randomItem = OBJ_MANAGER->GetPlayerWeapon(weaponType, itemNum);
		}
		break;
		case Item_Type::SUB_WEAPON:
			randomItem = OBJ_MANAGER->GetPlayerSubWeapon(itemNum);
			break;
		case Item_Type::ACCESSORY:
			randomItem = OBJ_MANAGER->GetPlayerAccessory(itemNum);
			break;
		case Item_Type::NONE:
			break;
		default:
			break;
		}
	}
	_dropItem = make_shared<DropItem>(randomItem->GetLevel(), randomItem->GetNum());
	_dropItem->SetItem(randomItem);
}

