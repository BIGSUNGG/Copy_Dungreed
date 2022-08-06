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
	shared_ptr<Object> object = GetTileObject(level, num);

	switch (type)
	{
	case Object::Object_Type::BACKGROUND:
		object = GetBackGroundObject(level, num);
		break;
	case Object::Object_Type::WALL:
		break;
	case Object::Object_Type::TILE:
		object = GetTileObject(level, num);
		break;
	case Object::Object_Type::CREATURE:
		break;
	case Object::Object_Type::EFFECT:
		break;
	default:
		break;
	}

	return object;
}

shared_ptr<Object> ObjectManager::GetBackGroundObject(int level, int num)
{
	shared_ptr<Object> object;
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Ui/MainLogo.png");


	switch (level)
	{
	case Map::LEVEL_00:
		switch (num)
		{
		case 0:
			texture = make_shared<Quad>(L"Resource/BackGround/Sky_Day.png");
			break;
		case 1:
			texture = make_shared<Quad>(L"Resource/BackGround/TownBG_Day.png");
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

	texture->GetTransform()->GetScale() *= WIN_RATIO;
	object = make_shared<BackGround>(level, num);
	object->SetTexture(texture);
	object->SetCollider();
	return object;
}

shared_ptr<Object> ObjectManager::GetWallObject(int level, int num)
{
	shared_ptr<BackGround> object;
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Ui/MainLogo.png");

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
		break;
	default:
		break;
	}

	texture->GetTransform()->GetScale() *= WIN_RATIO;
	object = make_shared<BackGround>(level, num);
	object->SetTexture(texture);
	object->SetCollider();
	return object;
}

shared_ptr<Object> ObjectManager::GetTileObject(int level, int num)
{
	shared_ptr<Tile> object;
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Ui/MainLogo.png");

	switch (level)
	{
	case Map::LEVEL_00:
		switch (num)
		{
		case 0:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_Broken0.png");
			break;
		case 1:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_OneWay_0.png");
			break;
		case 2:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_OneWay_1.png");
			break;
		case 3:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_OneWay_2.png");
			break;
		case 4:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_OneWay_3.png");
			break;
		case 5:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor0_1.png");
			break;
		case 6:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor3.png");
			break;
		case 7:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_LeftStair.png");
			break;
		case 8:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_LeftStair2.png");
			break;
		case 9:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_RightStair.png");
			break;
		case 10:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_RightStair2.png");
			break;
		case 11:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_TopCenter.png");
			break;
		case 12:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_TopLeft.png");
			break;
		case 13:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_TopRight.png");
			break;
		case 14:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_1.png");
			break;
		case 15:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_4.png");
			break;
		case 16:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_StairL.png");
			break;
		case 17:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_StairL2.png");
			break;
		case 18:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_StairR.png");
			break;
		case 19:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_StairR2.png");
			break;
		default:
			break;
	}
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

	texture->GetTransform()->GetScale() *= WIN_RATIO;
	object = make_shared<Tile>(level,num);
	object->SetTexture(texture);
	object->SetCollider();

	return object;
}