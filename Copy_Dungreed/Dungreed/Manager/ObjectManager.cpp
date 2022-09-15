#include "framework.h"
#include "ObjectManager.h"

ObjectManager* ObjectManager::_instance = nullptr;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

shared_ptr<Object> ObjectManager::GetNewObject(int type, int level, int num)
{
	shared_ptr<Object> object = GetTile(level, num);

	switch (type)
	{
	case Object::Object_Type::BACKGROUND:
		object = GetBackGround(level, num);
		break;
	case Object::Object_Type::WALL:
		object = GetWall(level, num);
		break;
	case Object::Object_Type::TILE:
		object = GetTile(level, num);
		break;
	case Object::Object_Type::CREATURE:
		object = GetCreature(level, num);
		break;
	case Object::Object_Type::EFFECT:
		object = GetCreatureEffect(level, num);
		break;
	default:
		break;
	}

	return object;
}

shared_ptr<BackGround> ObjectManager::GetBackGround(int level, int num)	
{
	shared_ptr<BackGround> object = make_shared<BackGround>(level, num);
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (level)
	{
	case Map::LEVEL_00:
		switch (num)
		{
		case 0:
			texture = make_shared<Quad>(L"Resource/BackGround/Sky_Day.png");
			object->GetBackGroundType() = BackGround::BackGround_Type::FOLLOW_CAMERA;
			break;
		case 1:
			texture = make_shared<Quad>(L"Resource/BackGround/TownBG_Day.png");
			object->GetBackGroundType() = BackGround::BackGround_Type::FOLLOW_PLAYER;
			break;
		case 2:
			texture = make_shared<Quad>(L"Resource/BackGround/TownLayer_Day.png");
			object->GetBackGroundType() = BackGround::BackGround_Type::FOLLOW_PLAYER;
			object->GetRatio() = 3.0f;
			break;
		default:
			break;
		}
		break;
	case Map::LEVEL_01:
		break;
	case Map::LEVEL_02:
		break;
	case Map::LEVEL_03:
		break;
	case Map::LEVEL_04:
		break;
	case Map::LEVEL_05:
		break;
	case Map::LEVEL_06:
		break;
	case Map::LEVEL_07:
		break;
	case Map::PUBLIC:
		break;
	default:
		break;
	}

	if (texture == nullptr)
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	if (object->GetTexture() == nullptr)
		object->SetTexture(texture);

	if (object->GetAnimation() != nullptr)
	{
		object->GetAnimation()->SetTexture(texture);
	}
	return object;
}

shared_ptr<Wall> ObjectManager::GetWall(int level, int num)
{
	shared_ptr<Wall> object = make_shared<Wall>(level, num);
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (level)
	{
	case Map::LEVEL_00:
		switch (num)
		{
		case 0:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Wall/Grass_H_4.png");
			break;
		case 1:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Wall/SecondFloor_Broken0.png");
			break;
		case 2:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Wall/SecondFloor0_1.png");
			break;
		case 3:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Wall/SecondFloor3.png");
			break;
		default:
			break;
		}
		break;
	case Map::LEVEL_01:
		break;
	case Map::LEVEL_02:
		break;
	case Map::LEVEL_03:
		break;
	case Map::LEVEL_04:
		break;
	case Map::LEVEL_05:
		break;
	case Map::LEVEL_06:
		break;
	case Map::LEVEL_07:
		break;
	case Map::PUBLIC:
		break;
	default:
		break;
	}

	if (texture == nullptr)
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	if (object->GetTexture() == nullptr)
		object->SetTexture(texture);

	if (object->GetAnimation() != nullptr)
	{
		object->GetAnimation()->SetTexture(texture);
	}
	return object;
}

shared_ptr<Tile> ObjectManager::GetTile(int level, int num)
{
	shared_ptr<Tile> object = make_shared<Tile>(level, num);
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (level)
	{
	case Map::LEVEL_00:
		switch (num)
		{
		case 0:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Grass_H_1.png");
			object->SetTexture(texture);
			object->GetCollider()->GetTransform()->GetScale().y *= 0.5f;
			object->GetCollider()->SetBottom(texture->Bottom());
			break;
		case 1:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Grass_H_1_1.png");
			object->SetTexture(texture);
			object->GetCollider()->GetTransform()->GetScale().y *= 0.5f;
			object->GetCollider()->SetBottom(texture->Bottom());
			break;
		case 2:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Grass_H_1_2.png");
			object->SetTexture(texture);
			object->GetCollider()->GetTransform()->GetScale().y *= 0.5f;
			object->GetCollider()->SetBottom(texture->Bottom());
			break;
		case 3:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Grass_H_1_3.png");
			object->SetTexture(texture);
			object->GetCollider()->GetTransform()->GetScale().y *= 0.5f;
			object->GetCollider()->SetBottom(texture->Bottom());
			break;
		case 4:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Grass_H_1_4.png");
			object->SetTexture(texture);
			object->GetCollider()->GetTransform()->GetScale().y *= 0.5f;
			object->GetCollider()->SetBottom(texture->Bottom());
			break;
		case 5:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Grass_H_1_5.png");
			object->SetTexture(texture);
			object->GetCollider()->GetTransform()->GetScale().y *= 0.5f;
			object->GetCollider()->SetBottom(texture->Bottom());
			break;
		case 6:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Grass_H_StairL.png");
			object->SetTexture(texture);
			object->GetCollider()->GetTransform()->GetScale().y *= 0.5f;
			object->GetCollider()->SetBottom(texture->Bottom());
			break;
		case 7:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Grass_H_StairL2.png");
			break;
		case 8:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Grass_H_StairR.png");
			object->SetTexture(texture);
			object->GetCollider()->GetTransform()->GetScale().y *= 0.5f;
			object->GetCollider()->SetBottom(texture->Bottom());
			break;
		case 9:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Grass_H_StairR2.png");
			break;
		case 10:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_OneWay_0.png");
			object->GetTileType() = Tile::Tile_Type::FLOOR;
			break;
		case 11:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_OneWay_1.png");
			object->GetTileType() = Tile::Tile_Type::FLOOR;
			break;
		case 12:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_OneWay_2.png");
			object->GetTileType() = Tile::Tile_Type::FLOOR;
			break;
		case 13:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_OneWay_3.png");
			object->GetTileType() = Tile::Tile_Type::FLOOR;
			break;
		case 14:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_LeftStair.png");
			object->GetTileType() = Tile::Tile_Type::FLOOR;
			break;
		case 15:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_LeftStair2.png");
			break;
		case 16:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_RightStair.png");
			break;
		case 17:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_RightStair2.png");
			break;
		case 18:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_TopCenter.png");
			break;
		case 19:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_TopLeft.png");
			break;
		case 20:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_TopRight.png");
			break;
		case 21:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_1.png");
			break;
		case 22:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_4.png");
			break;
		case 23:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_StairL.png");
			object->GetTileType() = Tile::Tile_Type::RIGHT_STAIR;
			break;
		case 24:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_StairL2.png");
			break;
		case 25:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_StairR.png");
			object->GetTileType() = Tile::Tile_Type::LEFT_STAIR;
			break;
		case 26:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_StairR2.png");
			break;
		}
		break;
	case Map::LEVEL_01:
		break;
	case Map::LEVEL_02:
		break;
	case Map::LEVEL_03:
		break;
	case Map::LEVEL_04:
		break;
	case Map::LEVEL_05:
		break;
	case Map::LEVEL_06:
		break;
	case Map::LEVEL_07:
		break;
	case Map::PUBLIC:
		break;
	default:
		break;
	}

	if (texture == nullptr)
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	if(object->GetTexture() == nullptr)
		object->SetTexture(texture);

	if (object->GetAnimation() != nullptr)
	{
		object->GetAnimation()->SetTexture(texture);
	}
	return object;
}

shared_ptr<Player> ObjectManager::GetPlayer(int num)
{
	shared_ptr<Player> object = make_shared<Player>(EXCEPT, num);
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (num)
	{
	case 0:
		object->SetAnimation();
		object->GetAnimation()->_animSpeed[Creature::State::IDLE] = vector<float>(5, 0.3f);
		object->GetAnimation()->_animState[Creature::State::IDLE] = Animation::Anim_State::LOOP;
		object->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Creature/Player/Adventurer/Idle/CharIdle0.png");
		object->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Creature/Player/Adventurer/Idle/CharIdle1.png");
		object->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Creature/Player/Adventurer/Idle/CharIdle2.png");
		object->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Creature/Player/Adventurer/Idle/CharIdle3.png");
		object->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Creature/Player/Adventurer/Idle/CharIdle4.png");

		object->GetAnimation()->_animSpeed[Creature::State::RUN] = vector<float>(8, 0.15f);
		object->GetAnimation()->_animState[Creature::State::RUN] = Animation::Anim_State::LOOP;
		object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun0.png");
		object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun1.png");
		object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun2.png");
		object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun3.png");
		object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun4.png");
		object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun5.png");
		object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun6.png");
		object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun7.png");

		object->GetAnimation()->_animSpeed[Creature::State::JUMP] = vector<float>(1, 0.15f);
		object->GetAnimation()->_animState[Creature::State::JUMP] = Animation::Anim_State::END;
		object->GetAnimation()->_animList[Creature::State::JUMP].push_back(L"Resource/Creature/Player/Adventurer/Jump/CharJump0.png");
		texture = make_shared<Quad>(object->GetAnimation()->_animList[Creature::State::IDLE][0]);
		break;
	default:
		break;
	}

	if (texture == nullptr)
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	if (object->GetTexture() == nullptr)
		object->SetTexture(texture);

	if (object->GetAnimation() != nullptr)
	{
		object->GetAnimation()->SetTexture(texture);
	}
	return object;
}

shared_ptr<Creature> ObjectManager::GetCreature(int level, int num)
{
	shared_ptr<Creature> object = make_shared<Creature>(level, num);
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");;
	shared_ptr<Weapon> weapon;

	switch (level)
	{
	case Map::LEVEL_00:
		switch (num)
		{
		case 0:
			object = make_shared<Monster>(level, num);

			object->SetAnimation();
			object->GetAnimation()->_animSpeed[Creature::State::IDLE] = vector<float>(1, 0.3f);
			object->GetAnimation()->_animState[Creature::State::IDLE] = Animation::Anim_State::LOOP;
			object->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Creature/Enemy/GraySkel/Idle/GraySkelIdle.png");

			object->GetAnimation()->_animSpeed[Creature::State::RUN] = vector<float>(6, 0.3f);
			object->GetAnimation()->_animState[Creature::State::RUN] = Animation::Anim_State::LOOP;
			object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk0.png");
			object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk1.png");
			object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk2.png");
			object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk3.png");
			object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk4.png");
			object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk5.png");

			texture = make_shared<Quad>(object->GetAnimation()->_animList[Creature::State::IDLE][0]);
			object->SetTexture(texture);
			weapon = GetEnemyWeapon(0, 0);
			object->AddWeapon(weapon);
			
			break;
		case 1:
			object = make_shared<Monster>(level, num);
			object->SetAnimation();
			object->GetAnimation()->_animSpeed[Creature::State::IDLE] = vector<float>(7, 0.3f);
			object->GetAnimation()->_animState[Creature::State::IDLE] = Animation::Anim_State::LOOP;
			object->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/Idle/BigWhiteSkelIdle.png");
			object->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/Idle/BigWhiteSkelIdle0.png");
			object->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/Idle/BigWhiteSkelIdle1.png");
			object->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/Idle/BigWhiteSkelIdle2.png");
			object->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/Idle/BigWhiteSkelIdle3.png");
			object->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/Idle/BigWhiteSkelIdle4.png");

			object->GetAnimation()->_animSpeed[Creature::State::ATTACK] = vector<float>(12, 0.15f);
			object->GetAnimation()->_animState[Creature::State::ATTACK] = Animation::Anim_State::LOOP;
			object->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/ATTACK/BigWhiteSkelAttack00.png");
			object->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/ATTACK/BigWhiteSkelAttack01.png");
			object->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/ATTACK/BigWhiteSkelAttack02.png");
			object->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/ATTACK/BigWhiteSkelAttack03.png");
			object->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/ATTACK/BigWhiteSkelAttack04.png");
			object->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/ATTACK/BigWhiteSkelAttack05.png");
			object->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/ATTACK/BigWhiteSkelAttack06.png");
			object->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/ATTACK/BigWhiteSkelAttack07.png");
			object->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/ATTACK/BigWhiteSkelAttack08.png");
			object->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/ATTACK/BigWhiteSkelAttack09.png");
			object->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/ATTACK/BigWhiteSkelAttack10.png");
			object->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/ATTACK/BigWhiteSkelAttack11.png");

			object->GetAnimation()->_animSpeed[Creature::State::RUN] = vector<float>(7, 0.15f);
			object->GetAnimation()->_animState[Creature::State::RUN] = Animation::Anim_State::LOOP;
			object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/Run/BigWhiteSkelMove0.png");
			object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/Run/BigWhiteSkelMove1.png");
			object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/Run/BigWhiteSkelMove2.png");
			object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/Run/BigWhiteSkelMove3.png");
			object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/Run/BigWhiteSkelMove4.png");
			object->GetAnimation()->_animList[Creature::State::RUN].push_back(L"Resource/Creature/Enemy/BigWhiteSkel/Run/BigWhiteSkelMove5.png");

			texture = make_shared<Quad>(object->GetAnimation()->_animList[Creature::State::IDLE][0]);
			break;
		default:
			break;
		}
		break;
	case Map::LEVEL_01:
		break;
	case Map::LEVEL_02:
		break;
	case Map::LEVEL_03:
		break;
	case Map::LEVEL_04:
		break;
	case Map::LEVEL_05:
		break;
	case Map::LEVEL_06:
		break;
	case Map::LEVEL_07:
		break;
	case Map::PUBLIC:
		break;
	default:
		break;
	}

	if (texture == nullptr)
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	if (object->GetTexture() == nullptr)
		object->SetTexture(texture);

	if (object->GetAnimation() != nullptr)
	{
		object->GetAnimation()->SetTexture(texture);
	}
	return object;
}

shared_ptr<Effect> ObjectManager::GetPlayerEffect(int num)
{
	shared_ptr<Effect> effect = make_shared<Effect>(EXCEPT, num);
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");
	
	switch (num)
	{
	case 0:
		effect->SetAnimation();
		effect->GetAnimation()->_animSpeed[BASIC] = vector<float>(7, 0.05f);
		effect->GetAnimation()->_animState[BASIC] = Animation::Anim_State::END;
		effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Player/Movement/Dust1.png");
		effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Player/Movement/Dust2.png");
		effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Player/Movement/Dust3.png");
		effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Player/Movement/Dust4.png");
		effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Player/Movement/Dust5.png");
		effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Player/Movement/Dust6.png");
		texture = make_shared<Quad>(effect->GetAnimation()->_animList[BASIC][BASIC]);
		break;
	case 1:
		effect->SetAnimation();
		effect->GetAnimation()->_animSpeed[BASIC] = vector<float>(7, 0.05f);
		effect->GetAnimation()->_animState[BASIC] = Animation::Anim_State::END;
		effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Player/Movement/DubleJumpFX0.png");
		effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Player/Movement/DubleJumpFX1.png");
		effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Player/Movement/DubleJumpFX2.png");
		effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Player/Movement/DubleJumpFX3.png");
		effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Player/Movement/DubleJumpFX4.png");
		effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Player/Movement/DubleJumpFX5.png");
		texture = make_shared<Quad>(effect->GetAnimation()->_animList[BASIC][BASIC]);
		break;
	default:
		break;
	}

	if (texture == nullptr)
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	if (effect->GetTexture() == nullptr)
		effect->SetTexture(texture);

	if (effect->GetAnimation() != nullptr)
	{
		effect->GetAnimation()->SetTexture(texture);
	}
	return effect;
}

shared_ptr<Effect> ObjectManager::GetCreatureEffect(int level, int num)
{
	shared_ptr<Effect> effect = make_shared<Effect>(level, num);
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (level)
	{
	case Map::LEVEL_00:
		break;
	case Map::LEVEL_01:
		break;
	case Map::LEVEL_02:
		break;
	case Map::LEVEL_03:
		break;
	case Map::LEVEL_04:
		break;
	case Map::LEVEL_05:
		break;
	case Map::LEVEL_06:
		break;
	case Map::LEVEL_07:
		break;
	case Map::PUBLIC:
		switch (num)
		{
		case 0:
			effect->SetAnimation();
			effect->GetAnimation()->GetRefreshSize() = true;

			effect->GetAnimation()->_animSpeed[BASIC] = vector<float>(11, 0.05f);
			effect->GetAnimation()->_animState[BASIC] = Animation::Anim_State::END;
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Die/Die00.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Die/Die01.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Die/Die02.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Die/Die03.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Die/Die04.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Die/Die05.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Die/Die06.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Die/Die07.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Die/Die08.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Die/Die09.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Die/Die10.png");

			texture = make_shared<Quad>(effect->GetAnimation()->_animList[BASIC][BASIC]);
			break;
		case 1:
			effect->SetAnimation();
			effect->GetAnimation()->GetRefreshSize() = true;

			effect->GetAnimation()->_animSpeed[BASIC] = vector<float>(15, 0.05f);
			effect->GetAnimation()->_animState[BASIC] = Animation::Anim_State::END;
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx00.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx01.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx02.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx03.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx04.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx05.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx06.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx07.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx08.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx09.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx10.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx11.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx12.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx13.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Creature/Spawn/MagicCircleFx14.png");

			texture = make_shared<Quad>(effect->GetAnimation()->_animList[BASIC][BASIC]);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (texture == nullptr)
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	if (effect->GetTexture() == nullptr)
		effect->SetTexture(texture);

	if (effect->GetAnimation() != nullptr)
	{
		effect->GetAnimation()->SetTexture(texture);
	}
	return effect;
}

shared_ptr<Effect> ObjectManager::GetPlayerWeaponEffect(int type, int num)
{
	shared_ptr<Effect> effect = make_shared<Effect>(type, num);
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (type)
	{
	case Weapon::MELEE:
		switch (num)
		{
		case 0:
			effect->SetAnimation();
			effect->GetAnimation()->_animSpeed[BASIC] = vector<float>(4, 0.1f);
			effect->GetAnimation()->_animState[BASIC] = Animation::Anim_State::END;
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/SwingFX00.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/SwingFX01.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/SwingFX02.png");
			texture = make_shared<Quad>(effect->GetAnimation()->_animList[BASIC][BASIC]);
			break;
		default:
			break;
		}
		break;
	case Weapon::GUN:
		break;
	case Weapon::SUB:
		break;
	default:
		break;
	}

	if (texture == nullptr)
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	if (effect->GetTexture() == nullptr)
		effect->SetTexture(texture);

	if (effect->GetAnimation() != nullptr)
	{
		effect->GetAnimation()->SetTexture(texture);
	}

	return effect;
}

shared_ptr<Effect> ObjectManager::GetEnemyWeaponEffect(int type, int num)
{
	shared_ptr<Effect> effect = make_shared<Effect>(type, num);
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (type)
	{
	case Weapon::MELEE:
		break;
	case Weapon::GUN:
		break;
	case Weapon::SUB:
		break;
	default:
		break;
	}

	if (texture == nullptr)
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	if (effect->GetTexture() == nullptr)
		effect->SetTexture(texture);

	if (effect->GetAnimation() != nullptr)
	{
		effect->GetAnimation()->SetTexture(texture);
	}

	return effect;
}

shared_ptr<Bullet> ObjectManager::GetPlayerBullet(int type, int num)
{
	shared_ptr<Bullet> bullet;
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (type)
	{
	case Weapon::MELEE:
		break;
	case Weapon::GUN:
		switch (num)
		{
		case 0:
			bullet = make_shared<Bullet>();
			texture = make_shared<Quad>(L"Resource/Effect/Weapon/Gun/CrossbowArrow.png");
			break;
		default:
			break;
		}
		break;
	case Weapon::SUB:
		break;
	default:
		break;
	}

	if (texture == nullptr)
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	if (bullet->GetTexture() == nullptr)
		bullet->SetTexture(texture);

	if (bullet->GetAnimation() != nullptr)
	{
		bullet->GetAnimation()->SetTexture(texture);
	}

	return bullet;
}

shared_ptr<Weapon> ObjectManager::GetPlayerWeapon(int type, int num)
{
	shared_ptr<Weapon> weapon;
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");
	function<shared_ptr<Effect>()> func;

	switch (type)
	{
	case Weapon::MELEE:
		switch (num)
		{
		case 0:
			weapon = make_shared<Melee>();
			func = bind(&ObjectManager::GetPlayerWeaponEffect, this, 0, 0);
			weapon->SetAttackRange({ 120,84 });
			weapon->SetAttackEffect(func);
			texture = make_shared<Quad>(L"Resource/Weapon/Melee/BasicShortSword_New.png");
			break;
		default:
			break;
		}
		break;
	case Weapon::GUN:
		switch (num)
		{
		case 0:
			weapon = make_shared<Gun>();
			texture = make_shared<Quad>(L"Resource/Weapon/Gun/MiniCrossbow2.png");
			break;
		default:
			break;
		}
		break;
	case Weapon::SUB:
		break;
	default:
		break;
	}

	if (texture == nullptr)
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	if (weapon->GetTexture() == nullptr)
		weapon->SetTexture(texture);

	if (weapon->GetAnimation() != nullptr)
	{
		weapon->GetAnimation()->SetTexture(texture);
	}
	return weapon;
}

shared_ptr<Weapon> ObjectManager::GetEnemyWeapon(int type, int num)
{
	shared_ptr<Weapon> weapon;
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (type)
	{
	case Map::LEVEL_00:
		switch (num)
		{
		case 0:
			weapon = make_shared<Melee>();

			weapon->SetOffset({ 70,-25 });
			weapon->SetAppendAngle({ 0.7f });
			weapon->SetGiveDamageDelay(0.8f);
			weapon->SetAttackRange({ 100,100 });

			weapon->SetAnimation();
			weapon->GetAnimation()->GetRefreshSize() = true;
			weapon->SetAttackDelay(1.0f);

			weapon->GetAnimation()->_animSpeed[Creature::State::IDLE] = vector<float>(1, 0.1f);
			weapon->GetAnimation()->_animState[Creature::State::IDLE] = Animation::Anim_State::END;
			weapon->GetAnimation()->_animList[Creature::State::IDLE].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword00.png");

			weapon->GetAnimation()->_animSpeed[Creature::State::ATTACK] = vector<float>(12, 0.1f);
			weapon->GetAnimation()->_animState[Creature::State::ATTACK] = Animation::Anim_State::END;
			weapon->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword00.png");
			weapon->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword01.png");
			weapon->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword02.png");
			weapon->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword03.png");
			weapon->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword04.png");
			weapon->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword05.png");
			weapon->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword06.png");
			weapon->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword07.png");
			weapon->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword08.png");
			weapon->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword09.png");
			weapon->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword10.png");
			weapon->GetAnimation()->_animList[Creature::State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword11.png");

			texture = make_shared<Quad>(weapon->GetAnimation()->_animList[BASIC][BASIC]);
			break;
		default:
			break;
		}
		break;
	case Map::LEVEL_01:
		break;
	case Map::LEVEL_02:
		break;
	case Map::LEVEL_03:
		break;
	case Map::LEVEL_04:
		break;
	case Map::LEVEL_05:
		break;
	case Map::LEVEL_06:
		break;
	case Map::LEVEL_07:
		break;
	case Map::PUBLIC:
		break;
	default:
		break;
	}

	if (texture == nullptr)
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	if (weapon->GetTexture() == nullptr)
		weapon->SetTexture(texture);

	if (weapon->GetAnimation() != nullptr)
	{
		weapon->GetAnimation()->SetTexture(texture);
	}

	return weapon;
}

shared_ptr<Quad> ObjectManager::GetCursur(int num)
{
	shared_ptr<Quad> texture;

	switch (num)
	{
	case 0:
		texture = make_shared<Quad>(L"Resource/Cursur/BasicCursor.png");
		break;
	case 1:
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor1.png");
		break;
	case 2:
		texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");
		break;
	default:
		break;
	}

	return texture;
}
