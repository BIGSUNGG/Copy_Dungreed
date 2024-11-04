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
	case Object::Object_Type::ETC:
		object = GetEtc(level, num);
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
			object->GetBackGroundType() = BackGround::BackGround_Type::WALLPAPER;
			break;
		case 1:
			texture = make_shared<Quad>(L"Resource/BackGround/TownBG_Day.png");
			object->GetBackGroundType() = BackGround::BackGround_Type::PERSPECTIVE;
			break;
		case 2:
			texture = make_shared<Quad>(L"Resource/BackGround/TownLayer_Day.png");
			object->GetBackGroundType() = BackGround::BackGround_Type::PERSPECTIVE;
			object->GetRatio() = 3.0f;
			break;
		default:
			break;
		}
		break;
	case Map::LEVEL_01:
		switch (num)
		{
		case 0:
			texture = make_shared<Quad>(L"Resource/BackGround/SubBG.png");
			object->GetBackGroundType() = BackGround::BackGround_Type::PERSPECTIVE;
			object->GetRatio() = 1.5f;
			break;
		}
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

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (object->GetObjectTexture() == nullptr)
		object->SetTexture(texture);

	if (object->GetAnimation() != nullptr)
		object->GetAnimation()->SetTexture(texture);

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
		}
		break;
	case Map::LEVEL_01:
		switch (num)
		{
		case 0:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_0.png");
			break;
		case 1:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_1.png");
			break;
		case 2:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_2.png");
			break;
		case 3:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_3.png");
			break;
		case 4:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_4.png");
			break;
		case 5:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_5.png");
			break;
		case 6:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_6.png");
			break;
		case 7:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_8.png");
			break;
		case 8:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_9.png");
			break;
		case 9:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_10.png");
			break;
		case 10:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_11.png");
			break;
		case 11:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_12.png");
			break;
		case 12:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_13.png");
			break;
		case 13:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_14.png");
			break;
		case 14:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_15.png");
			break;
		case 15:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_16.png");
			break;
		case 16:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_Ceiling_0.png");
			break;
		case 17:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_Ceiling_1.png");
			break;
		case 18:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_Ceiling_2.png");
			break;
		case 19:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_Ceiling_3.png");
			break;
		case 20:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_Ceiling_4.png");
			break;
		case 21:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_Ceiling_5.png");
			break;
		case 22:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_Ceiling_6.png");
			break;
		case 23:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_Statue_Bottom_0.png");
			break;
		case 24:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_Statue_Middle_0.png");
			break;
		case 25:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Basic_Statue_Top_0.png");
			break;
		case 26:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Board_Left.png");
			break;
		case 27:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Board_Left_Cracked.png");
			break;
		case 28:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Board_Middle_1.png");
			break;
		case 29:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Board_Right.png");
			break;
		case 30:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Board_Right_Cracked.png");
			break;
		case 31:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Board_Statue.png");
			break;
		case 32:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Chain.png");
			break;
		case 33:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Cracked_0.png");
			break;
		case 34:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Cracked_1.png");
			break;
		case 35:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Cracked_2.png");
			break;
		case 36:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Cracked_3.png");
			break;
		case 37:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Cracked_4.png");
			break;
		case 38:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Cracked_5.png");
			break;
		case 39:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_Cracked_6.png");
			break;
		case 40:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H_Hole1.png");
			break;
		case 41:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H_Hole2.png");
			break;
		case 42:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H0.png");
			break;
		case 43:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H1.png");
			break;
		case 44:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H2.png");
			break;
		case 45:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H3.png");
			break;
		case 46:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H4_0.png");
			break;
		case 47:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H4_1.png");
			break;
		case 48:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H4_2.png");
			break;
		case 49:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H4_3.png");
			break;
		case 50:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H5.png");
			break;
		case 51:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H6.png");
			break;
		case 52:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H7.png");
			break;
		case 53:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H8.png");
			break;
		case 54:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H9.png");
			break;
		case 55:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H10.png");
			break;
		case 56:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H11.png");
			break;
		case 57:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Wall/Wall_H12.png");
			break;
		default:
			break;
		}
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
			texture = make_shared<Quad>(L"Resource/Map/Public/Door/Door9 #214938.png");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (object->GetObjectTexture() == nullptr)
		object->SetTexture(texture);

	if (object->GetAnimation() != nullptr)
		object->GetAnimation()->SetTexture(texture);

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
		case 27:
			texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Grass_H_4.png");
			object->SetIsCollision(false);
			break;
		}
		break;
	case Map::LEVEL_01:
		switch (num)
		{
		case 0:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Basic_H_Type2_0.png");
			break;
		case 1:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Basic_H_Type2_1.png");
			break;
		case 2:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Basic_H_Type2_2.png");
			break;
		case 3:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Basic_H_Type2_3.png");
			break;
		case 4:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Basic_H_Type2_4.png");
			break;
		case 5:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Basic_H_Type2_5.png");
			break;
		case 6:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Basic_H_Type2_6.png");
			break;
		case 7:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Basic_H_Type2_7.png");
			break;
		case 8:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Basic_H_Type2_8.png");
			break;
		case 9:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicDirt_Bottom.png");
			break;
		case 10:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicDirt_Middle.png");
			break;
		case 11:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicDirt_Top.png");
			break;
		case 12:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_BottomCenter.png");
			break;
		case 13:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_BottomLeft.png");
			break;
		case 14:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_BottomRight.png");
			break;
		case 15:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_MiddleCenter_0.png");
			break;
		case 16:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_MiddleCenter_1.png");
			break;
		case 17:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_MiddleCenter_2.png");
			break;
		case 18:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_MiddleCenter_3.png");
			break;
		case 19:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_MiddleCenter_4.png");
			break;
		case 20:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_MiddleCenter_5.png");
			break;
		case 21:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_MiddleCenter_6.png");
			break;
		case 22:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_MiddleCenter_7.png");
			break;
		case 23:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_MiddleLeft.png");
			break;
		case 24:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_MiddleRight.png");
			break;
		case 25:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopCenter_0.png");
			break;
		case 26:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopCenter_1.png");
			break;
		case 27:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopCenter_2.png");
			break;
		case 28:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopCenter_3.png");
			break;
		case 29:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopCenter_4.png");
			break;
		case 30:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopCenter_5.png");
			break;
		case 31:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopCenter_6.png");
			break;
		case 32:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopCenter_7.png");
			break;
		case 33:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopCenter_8.png");
			break;
		case 34:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopLeft.png");
			break;
		case 35:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopRight.png");
			break;
		case 36:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H0.png");
			break;
		case 37:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H1.png");
			break;
		case 38:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H2.png");
			break;
		case 39:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H3.png");
			break;
		case 40:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H4.png");
			break;
		case 41:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H5.png");
			break;
		case 42:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H6.png");
			break;
		case 43:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H7.png");
			break;
		case 44:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H8.png");
			break;
		case 45:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H9.png");
			break;
		case 46:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H10.png");
			break;
		case 47:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H11.png");
			break;
		case 48:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H12.png");
			break;
		case 49:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H13.png");
			break;
		case 50:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H14.png");
			break;
		case 51:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_H15.png");
			break;
		case 52:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Marble_Stair_BottomLeft.png");
			break;
		case 53:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Marble_Stair_BottomRight.png");
			break;
		case 54:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Marble_Stair_TopLeft.png");
			break;
		case 55:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Marble_Stair_TopRight.png");
			break;
		case 56:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Marble_Top.png");
			break;
		case 57:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Slim_BottomCenter.png");
			break;
		case 58:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Slim_BottomLeft.png");
			break;
		case 59:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Slim_BottomRight.png");
			break;
		case 60:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Slim_Left.png");
			break;
		case 61:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Slim_MiddleLeft.png");
			break;
		case 62:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Slim_MiddleRight.png");
			break;
		case 63:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Slim_Right.png");
			break;
		case 64:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Slim_Top.png");
			break;
		case 65:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Slim_TopCenter.png");
			break;
		case 66:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Slim_TopLeft.png");
			break;
		case 67:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Slim_TopRight.png");
			break;
		case 68:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Stair_BottomLeft.png");
			break;
		case 69:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Stair_BottomRight.png");
			break;
		case 70:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Stair_TopLeft.png");
			object->GetTileType() = Tile::LEFT_STAIR;
			break;
		case 71:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Stair_TopRight.png");
			object->GetTileType() = Tile::RIGHT_STAIR;
			break;
		case 72:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Vertical1TileBottom.png");
			break;
		case 73:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Vertical1TileMiddle.png");
			break;
		case 74:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Vertical1TileTop.png");
			break;
		case 75:
			texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/OneWayPlatform.png");
			object->GetTileType() = Tile::FLOOR;
			break;
		default:
			break;
		}
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

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (object->GetObjectTexture() == nullptr)
		object->SetTexture(texture);

	if (object->GetAnimation() != nullptr)
		object->GetAnimation()->SetTexture(texture);

	return object;
}

shared_ptr<Etc> ObjectManager::GetEtc(int type, int num)
{
	shared_ptr<Etc> object = make_shared<Etc>(type, num);
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (type)
	{
	case Etc::UNKNOWN:
		break;
	case Etc::ITEM:
		break;
	case Etc::BULLET:
		break;
	case Etc::CHEST:
	{
		shared_ptr<Chest> chest = make_shared<Chest>(type, num);
		switch (num)
		{
		case 0:
			object = chest;
			chest->SetOpenTexture(L"Resource/Map/Public/Chest/BasicTresureOpened.png");
			texture = make_shared<Quad>(L"Resource/Map/Public/Chest/BasicTresureClosed.png");
			break;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (object->GetObjectTexture() == nullptr)
		object->SetTexture(texture);

	if (object->GetAnimation() != nullptr)
		object->GetAnimation()->SetTexture(texture);

	object->SetCollider();

	return object;
}

shared_ptr<Player> ObjectManager::GetPlayer(int num)
{
	shared_ptr<Player> object = make_shared<Player>(EXCEPT, num);
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (num)
	{
	case 0:
		object->CreateAnimation();
		object->GetAnimation()->_animSpeed[Creature::Creature_State::IDLE] = vector<float>(5, 0.1f);
		object->GetAnimation()->_animState[Creature::Creature_State::IDLE] = Animation::Anim_State::LOOP;
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Adventurer/Idle/CharIdle0.png");
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Adventurer/Idle/CharIdle1.png");
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Adventurer/Idle/CharIdle2.png");
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Adventurer/Idle/CharIdle3.png");
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Adventurer/Idle/CharIdle4.png");

		object->GetAnimation()->_animSpeed[Creature::Creature_State::RUN] = vector<float>(8, 0.1f);
		object->GetAnimation()->_animState[Creature::Creature_State::RUN] = Animation::Anim_State::LOOP;
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun0.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun1.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun2.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun3.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun4.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun5.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun6.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Adventurer/Run/CharRun7.png");

		object->GetAnimation()->_animSpeed[Creature::Creature_State::JUMP] = vector<float>(1, 0.1f);
		object->GetAnimation()->_animState[Creature::Creature_State::JUMP] = Animation::Anim_State::END;
		object->GetAnimation()->_animList[Creature::Creature_State::JUMP].push_back(L"Resource/Creature/Player/Adventurer/Jump/CharJump0.png");
		texture = make_shared<Quad>(object->GetAnimation()->_animList[Creature::Creature_State::IDLE][0]);
		break;
	case 1:
		object->CreateAnimation();
		object->GetAnimation()->_animSpeed[Creature::Creature_State::IDLE] = vector<float>(5, 0.1f);
		object->GetAnimation()->_animState[Creature::Creature_State::IDLE] = Animation::Anim_State::LOOP;
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Alice/Idle/CharIdle0.png");
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Alice/Idle/CharIdle1.png");
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Alice/Idle/CharIdle2.png");
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Alice/Idle/CharIdle3.png");
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Alice/Idle/CharIdle4.png");

		object->GetAnimation()->_animSpeed[Creature::Creature_State::RUN] = vector<float>(6, 0.1f);
		object->GetAnimation()->_animState[Creature::Creature_State::RUN] = Animation::Anim_State::LOOP;
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Alice/Run/CharRun0.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Alice/Run/CharRun1.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Alice/Run/CharRun2.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Alice/Run/CharRun3.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Alice/Run/CharRun4.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Alice/Run/CharRun5.png");

		object->GetAnimation()->_animSpeed[Creature::Creature_State::JUMP] = vector<float>(1, 0.1f);
		object->GetAnimation()->_animState[Creature::Creature_State::JUMP] = Animation::Anim_State::END;
		object->GetAnimation()->_animList[Creature::Creature_State::JUMP].push_back(L"Resource/Creature/Player/Alice/Jump/CharJump0.png");
		texture = make_shared<Quad>(object->GetAnimation()->_animList[Creature::Creature_State::IDLE][0]);
		break;
	case 2:
		object->CreateAnimation();
		object->GetAnimation()->_animSpeed[Creature::Creature_State::IDLE] = vector<float>(5, 0.1f);
		object->GetAnimation()->_animState[Creature::Creature_State::IDLE] = Animation::Anim_State::LOOP;
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Sesilia/Idle/Sesilia_Idle00.png");
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Sesilia/Idle/Sesilia_Idle01.png");
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Sesilia/Idle/Sesilia_Idle02.png");
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Sesilia/Idle/Sesilia_Idle03.png");
		object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Player/Sesilia/Idle/Sesilia_Idle04.png");

		object->GetAnimation()->_animSpeed[Creature::Creature_State::RUN] = vector<float>(8, 0.1f);
		object->GetAnimation()->_animState[Creature::Creature_State::RUN] = Animation::Anim_State::LOOP;
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Sesilia/Run/Sesilia_Move00.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Sesilia/Run/Sesilia_Move01.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Sesilia/Run/Sesilia_Move02.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Sesilia/Run/Sesilia_Move03.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Sesilia/Run/Sesilia_Move04.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Sesilia/Run/Sesilia_Move05.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Sesilia/Run/Sesilia_Move06.png");
		object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Player/Sesilia/Run/Sesilia_Move07.png");

		object->GetAnimation()->_animSpeed[Creature::Creature_State::JUMP] = vector<float>(1, 0.1f);
		object->GetAnimation()->_animState[Creature::Creature_State::JUMP] = Animation::Anim_State::END;
		object->GetAnimation()->_animList[Creature::Creature_State::JUMP].push_back(L"Resource/Creature/Player/Sesilia/Jump/Sesilia_Jump00.png");
		texture = make_shared<Quad>(object->GetAnimation()->_animList[Creature::Creature_State::IDLE][0]);
		break;
	default:
		break;
	}

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (object->GetObjectTexture() == nullptr)
		object->SetTexture(texture);

	if (object->GetAnimation() != nullptr)
		object->GetAnimation()->SetTexture(texture);

	shared_ptr<RectCollider> collider = make_shared<RectCollider>(Vector2(35, 67));
	object->SetCollider(collider);

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
			object = make_shared<GraySkel>(level, num);

			object->CreateAnimation();
			object->GetAnimation()->_animSpeed[Creature::Creature_State::IDLE] = vector<float>(1, 0.3f);
			object->GetAnimation()->_animState[Creature::Creature_State::IDLE] = Animation::Anim_State::LOOP;
			object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Enemy/GraySkel/Idle/GraySkelIdle.png");

			object->GetAnimation()->_animSpeed[Creature::Creature_State::RUN] = vector<float>(6, 0.3f);
			object->GetAnimation()->_animState[Creature::Creature_State::RUN] = Animation::Anim_State::LOOP;
			object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk0.png");
			object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk1.png");
			object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk2.png");
			object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk3.png");
			object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk4.png");
			object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk5.png");

			texture = make_shared<Quad>(object->GetAnimation()->_animList[Creature::Creature_State::IDLE][0]);
			object->SetTexture(texture);
			weapon = GetEnemyWeapon(0, 0);
			object->GainItem(weapon);
			break;
		case 1:		
			object = make_shared<GraySkel>(level, num);

			object->CreateAnimation();
			object->GetAnimation()->_animSpeed[Creature::Creature_State::IDLE] = vector<float>(1, 0.3f);
			object->GetAnimation()->_animState[Creature::Creature_State::IDLE] = Animation::Anim_State::LOOP;
			object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Enemy/GraySkel/Idle/GraySkelIdle.png");

			object->GetAnimation()->_animSpeed[Creature::Creature_State::RUN] = vector<float>(6, 0.3f);
			object->GetAnimation()->_animState[Creature::Creature_State::RUN] = Animation::Anim_State::LOOP;
			object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk0.png");
			object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk1.png");
			object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk2.png");
			object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk3.png");
			object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk4.png");
			object->GetAnimation()->_animList[Creature::Creature_State::RUN].push_back(L"Resource/Creature/Enemy/GraySkel/Run/GraySkelWalk5.png");

			texture = make_shared<Quad>(object->GetAnimation()->_animList[Creature::Creature_State::IDLE][0]);
			object->SetTexture(texture);
			weapon = GetEnemyWeapon(0, 1);
			object->GainItem(weapon);
			break;
		case 2:
			object = make_shared<Ghost>(level, num);

			object->CreateAnimation();
			object->GetAnimation()->_animSpeed[Creature::Creature_State::IDLE] = vector<float>(6, 0.15f);
			object->GetAnimation()->_animState[Creature::Creature_State::IDLE] = Animation::Anim_State::LOOP;
			object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Enemy/Ghost/Idle/LittleGhost0.png");
			object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Enemy/Ghost/Idle/LittleGhost1.png");
			object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Enemy/Ghost/Idle/LittleGhost2.png");
			object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Enemy/Ghost/Idle/LittleGhost3.png");
			object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Enemy/Ghost/Idle/LittleGhost4.png");
			object->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Creature/Enemy/Ghost/Idle/LittleGhost5.png");

			object->GetAnimation()->_animSpeed[Creature::Creature_State::ATTACK] = vector<float>(3, 0.15f);
			object->GetAnimation()->_animState[Creature::Creature_State::ATTACK] = Animation::Anim_State::LOOP;
			object->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Creature/Enemy/Ghost/Attack/LittleGhostAttack0.png");
			object->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Creature/Enemy/Ghost/Attack/LittleGhostAttack1.png");
			object->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Creature/Enemy/Ghost/Attack/LittleGhostAttack2.png");

			texture = make_shared<Quad>(object->GetAnimation()->_animList[Creature::Creature_State::IDLE][0]);

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

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (object->GetObjectTexture() == nullptr)
		object->SetTexture(texture);

	if (object->GetAnimation() != nullptr)
		object->GetAnimation()->SetTexture(texture);

	return object;
}

shared_ptr<Effect> ObjectManager::GetPlayerEffect(int num)
{
	shared_ptr<Effect> effect = make_shared<Effect>(EXCEPT, num);
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");
	
	switch (num)
	{
	case 0:
		effect->CreateAnimation();
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
		effect->CreateAnimation();
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

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (effect->GetObjectTexture() == nullptr)
		effect->SetTexture(texture);

	if (effect->GetAnimation() != nullptr)
		effect->GetAnimation()->SetTexture(texture);

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
			effect->CreateAnimation();

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
			effect->CreateAnimation();

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

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (effect->GetObjectTexture() == nullptr)
		effect->SetTexture(texture);

	if (effect->GetAnimation() != nullptr)
		effect->GetAnimation()->SetTexture(texture);

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
			effect->CreateAnimation();
			effect->GetAnimation()->_animSpeed[BASIC] = vector<float>(4, 0.1f);
			effect->GetAnimation()->_animState[BASIC] = Animation::Anim_State::END;
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/BasicSword/SwingFX00.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/BasicSword/SwingFX01.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/BasicSword/SwingFX02.png");
			texture = make_shared<Quad>(effect->GetAnimation()->_animList[BASIC][BASIC]);
			break;
		case 1:
			effect->CreateAnimation();
			effect->GetAnimation()->_animSpeed[BASIC] = vector<float>(6, 0.075f);
			effect->GetAnimation()->_animState[BASIC] = Animation::Anim_State::END;
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/FireDrangonKiller/FireGreatSwingFX01.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/FireDrangonKiller/FireGreatSwingFX02.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/FireDrangonKiller/FireGreatSwingFX03.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/FireDrangonKiller/FireGreatSwingFX04.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/FireDrangonKiller/FireGreatSwingFX05.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/FireDrangonKiller/FireGreatSwingFX06.png");
			texture = make_shared<Quad>(effect->GetAnimation()->_animList[BASIC][BASIC]);
			break;
		case 2:
			effect->CreateAnimation();
			effect->GetAnimation()->_animSpeed[BASIC] = vector<float>(8, 0.1f);
			effect->GetAnimation()->_animState[BASIC] = Animation::Anim_State::END;
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosSwingFX00.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosSwingFX01.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosSwingFX02.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosSwingFX03.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosSwingFX04.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosSwingFX05.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosSwingFX06.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosSwingFX07.png");
			texture = make_shared<Quad>(effect->GetAnimation()->_animList[BASIC][BASIC]);
			break;
		default:
			break;
		}
		break;
	case Weapon::GUN:
		switch (num)
		{
		case 0:
			effect->CreateAnimation();
			effect->GetAnimation()->_animSpeed[BASIC] = vector<float>(6, 0.05f);
			effect->GetAnimation()->_animState[BASIC] = Animation::Anim_State::END;
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Gun/Bullet/Destroy/ArrowFX0.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Gun/Bullet/Destroy/ArrowFX1.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Gun/Bullet/Destroy/ArrowFX2.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Gun/Bullet/Destroy/ArrowFX3.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Gun/Bullet/Destroy/ArrowFX4.png");
			effect->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Gun/Bullet/Destroy/ArrowFX5.png");
			texture = make_shared<Quad>(effect->GetAnimation()->_animList[BASIC][BASIC]);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (effect->GetObjectTexture() == nullptr)
		effect->SetTexture(texture);

	if (effect->GetAnimation() != nullptr)
		effect->GetAnimation()->SetTexture(texture);

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
	default:
		break;
	}

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (effect->GetObjectTexture() == nullptr)
		effect->SetTexture(texture);

	if (effect->GetAnimation() != nullptr)
		effect->GetAnimation()->SetTexture(texture);

	return effect;
}

shared_ptr<DropGold> ObjectManager::GetGold(int num)
{
	shared_ptr<DropGold> gold = make_shared<DropGold>(0, 0);
	shared_ptr<Quad> texture;

	switch (num)
	{
	case 0:
		gold->SetGoldValue(MathUtility::RandomInt(5,10));
		gold->CreateAnimation();
		gold->GetAnimation()->_animSpeed[BASIC] = vector<float>(7, 0.1f);
		gold->GetAnimation()->_animState[BASIC] = Animation::Anim_State::LOOP;
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/GoldCoin1.png");
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/GoldCoin2.png");
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/GoldCoin3.png");
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/GoldCoin4.png");
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/GoldCoin5.png");
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/GoldCoin6.png");
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/GoldCoin7.png");
		texture = make_shared<Quad>(gold->GetAnimation()->_animList[BASIC][BASIC]);
		break;
	case 1:
		gold->SetGoldValue(MathUtility::RandomInt(80, 100));
		gold->CreateAnimation();
		gold->GetAnimation()->_animSpeed[BASIC] = vector<float>(7, 0.1f);
		gold->GetAnimation()->_animState[BASIC] = Animation::Anim_State::LOOP;
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/Bullion0.png");
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/Bullion1.png");
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/Bullion2.png");
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/Bullion3.png");
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/Bullion4.png");
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/Bullion5.png");
		gold->GetAnimation()->_animList[BASIC].push_back(L"Resource/Map/Public/Gold/Bullion6.png");
		texture = make_shared<Quad>(gold->GetAnimation()->_animList[BASIC][BASIC]);
		break;
	default:
		break;
	}


	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (gold->GetObjectTexture() == nullptr)
		gold->SetTexture(texture);

	if (gold->GetAnimation() != nullptr)
		gold->GetAnimation()->SetTexture(texture);

	return gold;
}

shared_ptr<Bullet> ObjectManager::GetBullet(int type, int num)
{
	shared_ptr<Bullet> bullet;
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");
	function<shared_ptr<Effect>()> func;

	switch (type)
	{
	case Weapon::MELEE:
		switch (num)
		{
		case 0:
			break;
		case 2:
			bullet = make_shared<Bullet>(type, num);
			bullet->SetDestroyTime(2.f);
			bullet->SetHitCount(INT_MAX);

			bullet->CreateAnimation();
			bullet->GetAnimation()->_animSpeed[BASIC] = vector<float>(5, 0.05f);
			bullet->GetAnimation()->_animState[BASIC] = Animation::Anim_State::LOOP;
			bullet->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosAuror00.png");
			bullet->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosAuror01.png");
			bullet->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosAuror02.png");
			bullet->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosAuror03.png");
			bullet->GetAnimation()->_animList[BASIC].push_back(L"Resource/Effect/Weapon/Melee/Cosmos/CosmosAuror04.png");
			texture = make_shared<Quad>(bullet->GetAnimation()->_animList[BASIC][BASIC]);
			break;
		default:
			break;
		}
		break;
	case Weapon::GUN:
		switch (num)
		{
		case 0:
			bullet = make_shared<Bullet>(type ,num);
			func = bind(&ObjectManager::GetPlayerWeaponEffect, this, Weapon::GUN, 0);
			bullet->SetDestroyEffect(func);
			texture = make_shared<Quad>(L"Resource/Effect/Weapon/Gun/Bullet/CrossbowArrow.png");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (bullet->GetObjectTexture() == nullptr)
		bullet->SetTexture(texture);

	if (bullet->GetAnimation() != nullptr)
		bullet->GetAnimation()->SetTexture(texture);

	return bullet;
}

shared_ptr<Weapon> ObjectManager::GetPlayerWeapon(int type, int num)
{
	shared_ptr<Weapon> weapon;
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");
	function<shared_ptr<Effect>()> effect;
	function<void()> skill;

	switch (type)
	{
	case Weapon::MELEE:
		switch (num)
		{
		case 0:
			weapon = make_shared<Melee>(type,num);
			effect = bind(&ObjectManager::GetPlayerWeaponEffect, this, type, num);
			weapon->SetAttackMinDamage(10.f); 
			weapon->SetAttackMaxDamage(20.f);
			weapon->SetAttackRange({ 84,120 });
			weapon->SetAttackEffect(effect);
			weapon->SetAppendAngle({ -0.1f,1.2f });
			texture = make_shared<Quad>(L"Resource/Weapon/Melee/BasicShortSword/BasicShortSword_New.png");
			SOUND->Add("swing2", "Resource/Sound/Weapon/Swing/swing2.wav");
			weapon->SetAttackSound("swing2");
			weapon->SetIconTexture(L"Resource/Weapon/Melee/BasicShortSword/BasicShortSword_New.png");
			break;
		case 1:
			weapon = make_shared<Melee_FireDragonKiller>(type, num);
			texture = make_shared<Quad>(L"Resource/Weapon/Melee/FireDragonKiller/FireDragonKiller.png");
			effect = bind(&ObjectManager::GetPlayerWeaponEffect, this, type, num);
			weapon->SetAttackMinDamage(30.f);
			weapon->SetAttackMaxDamage(50.f);
			weapon->SetIconTexture(L"Resource/Weapon/Melee/FireDragonKiller/FireDragonKiller.png");
			weapon->SetAttackEffect(effect);
			weapon->SetAttackRange({ 130,180 });
			weapon->SetAppendAngle({ -0.1f,1.2f });
			weapon->SetAttackDelay(0.75f);
			break;
		case 2:
			weapon = make_shared<Melee>(type, num);
			effect = bind(&ObjectManager::GetPlayerWeaponEffect, this, type, num);
			weapon->SetAttackMinDamage(15.f);
			weapon->SetAttackMaxDamage(20.f);
			weapon->SetAttackRange({ 130,180 });
			weapon->SetAttackDelay(0.25f);
			weapon->SetSkillDelay(2.f);
			weapon->SetAttackEffect(effect);
			weapon->SetAppendAngle({ -0.1f,1.2f });
			weapon->CreateAnimation();
			weapon->GetAnimation()->_animSpeed[Item_State::IDLE] = vector<float>(12, 0.1f);
			weapon->GetAnimation()->_animState[Item_State::IDLE] = Animation::Anim_State::LOOP;
			weapon->GetAnimation()->_animList[Item_State::IDLE].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSword00.png");
			weapon->GetAnimation()->_animList[Item_State::IDLE].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSword01.png");
			weapon->GetAnimation()->_animList[Item_State::IDLE].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSword02.png");
			weapon->GetAnimation()->_animList[Item_State::IDLE].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSword03.png");
			weapon->GetAnimation()->_animList[Item_State::IDLE].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSword04.png");
			weapon->GetAnimation()->_animList[Item_State::IDLE].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSword05.png");
			weapon->GetAnimation()->_animList[Item_State::IDLE].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSword06.png");
			weapon->GetAnimation()->_animList[Item_State::IDLE].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSword07.png");
			weapon->GetAnimation()->_animList[Item_State::IDLE].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSword08.png");
			weapon->GetAnimation()->_animList[Item_State::IDLE].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSword09.png");
			weapon->GetAnimation()->_animList[Item_State::IDLE].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSword10.png");
			weapon->GetAnimation()->_animList[Item_State::IDLE].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSword11.png");

			weapon->GetAnimation()->_animSpeed[Item_State::SKILL] = vector<float>(3, 0.1f);
			weapon->GetAnimation()->_animState[Item_State::SKILL] = Animation::Anim_State::END;
			weapon->GetAnimation()->_animList[Item_State::SKILL].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSwordSkill00.png");
			weapon->GetAnimation()->_animList[Item_State::SKILL].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSwordSkill01.png");
			weapon->GetAnimation()->_animList[Item_State::SKILL].push_back(L"Resource/Weapon/Melee/CosmosSword/CosmosSwordSkill02.png");

			texture = make_shared<Quad>(weapon->GetAnimation()->_animList[Item_State::IDLE][BASIC]);
			SOUND->Add("CosmicDash", "Resource/Sound/Weapon/Swing/CosmicDash.wav");
			weapon->SetAttackSound("CosmicDash");
			weapon->SetIconTexture(L"Resource/Weapon/Melee/CosmosSword/CosmosSword00.png");

			skill = [=]() {
				SOUND->Play("CosmicDash");
				weapon->AddOffsetIndex(1);

				shared_ptr<Bullet> _bullet = MAKE_BULLET(type, num);
				_bullet->GetObjectTexture()->GetTransform()->GetPos() = weapon->GetSpringArm()->GetWorldPos();
				_bullet->GetObjectTexture()->GetTransform()->GetAngle() = weapon->GetShowDirection() - (0.5f * PI);

				float angle = weapon->GetShowDirection() / PI;
				Vector2 direction = { 1.0f,tan(weapon->GetShowDirection()) };

				if (angle > 0.5f || angle < -0.5f)
					direction *= -1;

				direction.Normalize();

				_bullet->SetDirection(direction);
				_bullet->SetSpeed(2500.0f);
				_bullet->SetOwner(weapon);

				GAME->AddEtcObject(_bullet);
			};
			weapon->SetSkill(skill, L"Resource/Skill/Skill_CosmosSwordAuror.png");
			break;
		default:
			break;
		}
		break;
	case Weapon::GUN:
		switch (num)
		{
		case 0:
			weapon = make_shared<Gun>(type,num);
			texture = make_shared<Quad>(L"Resource/Weapon/Gun/MiniCrossbow2.png");
			weapon->SetAttackMinDamage(15.f);
			weapon->SetAttackMaxDamage(25.f);
			weapon->SetIconTexture(L"Resource/Weapon/Gun/MiniCrossbow2.png");
			weapon->SetAttackDelay(0.5f);
			SOUND->Add("crossbow", "Resource/Sound/Weapon/Fire/crossbow.wav");
			weapon->SetAttackSound("crossbow");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (weapon != nullptr)
	{
		if (weapon->GetObjectTexture() == nullptr)
			weapon->SetTexture(texture);

		if (weapon->GetAnimation() != nullptr)
			weapon->GetAnimation()->SetTexture(texture);
	}

	return weapon;
}

shared_ptr<SubWeapon> ObjectManager::GetPlayerSubWeapon(int num)
{
	shared_ptr<SubWeapon> subWeapon;
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (num)
	{
	default:
		break;
	}

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (subWeapon != nullptr)
	{
		if (subWeapon->GetObjectTexture() == nullptr)
			subWeapon->SetTexture(texture);

		if (subWeapon->GetAnimation() != nullptr)
			subWeapon->GetAnimation()->SetTexture(texture);
	}

	return subWeapon;
}

shared_ptr<Accessory> ObjectManager::GetPlayerAccessory(int num)
{
	shared_ptr<Accessory> accessory;
	shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");

	switch (num)
	{
	default:
		break;
	}

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (accessory != nullptr)
	{
		if (accessory->GetObjectTexture() == nullptr)
			accessory->SetTexture(texture);

		if (accessory->GetAnimation() != nullptr)
			accessory->GetAnimation()->SetTexture(texture);
	}

	return accessory;
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
			weapon = make_shared<Melee>(type,num);

			weapon->SetOffset({ 70,-55 });
			weapon->SetAppendAngle({ 0.f });
			weapon->SetGiveDamageDelay(0.8f);
			weapon->SetAttackRange({ 70, 100});

			weapon->CreateAnimation();
			weapon->SetAttackDelay(1.0f);

			weapon->GetAnimation()->_animSpeed[Creature::Creature_State::IDLE] = vector<float>(1, 0.1f);
			weapon->GetAnimation()->_animState[Creature::Creature_State::IDLE] = Animation::Anim_State::END;
			weapon->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword00.png");

			weapon->GetAnimation()->_animSpeed[Creature::Creature_State::ATTACK] = vector<float>(12, 0.1f);
			weapon->GetAnimation()->_animState[Creature::Creature_State::ATTACK] = Animation::Anim_State::END;
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword00.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword01.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword02.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword03.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword04.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword05.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword06.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword07.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword08.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword09.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword10.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyShortSword11.png");

			weapon->SetIconTexture(weapon->GetAnimation()->_animList[BASIC][BASIC]);
			texture = make_shared<Quad>(weapon->GetAnimation()->_animList[BASIC][BASIC]);
			break;
		case 1:
			weapon = make_shared<Melee>(type, num);

			weapon->SetOffset({ 45,-55 });
			weapon->SetAppendAngle({ 0.f });
			weapon->SetGiveDamageDelay(0.7f);
			weapon->SetAttackRange({ 100,150 });

			weapon->CreateAnimation();
			weapon->SetAttackDelay(1.0f);

			weapon->GetAnimation()->_animSpeed[Creature::Creature_State::IDLE] = vector<float>(1, 0.1f);
			weapon->GetAnimation()->_animState[Creature::Creature_State::IDLE] = Animation::Anim_State::END;
			weapon->GetAnimation()->_animList[Creature::Creature_State::IDLE].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword00.png");

			weapon->GetAnimation()->_animSpeed[Creature::Creature_State::ATTACK] = vector<float>(15, 0.1f);
			weapon->GetAnimation()->_animState[Creature::Creature_State::ATTACK] = Animation::Anim_State::END;
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword00.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword01.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword02.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword03.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword04.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword05.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword06.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword07.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword08.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword09.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword10.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword11.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword12.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword13.png");
			weapon->GetAnimation()->_animList[Creature::Creature_State::ATTACK].push_back(L"Resource/Weapon/Enemy/GraySkel/RustyGreatSword14.png");

			weapon->SetIconTexture(weapon->GetAnimation()->_animList[BASIC][BASIC]);
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

	assert(texture != nullptr);
	assert(texture->GetSize() != Vector2(0, 0));

	if (weapon->GetObjectTexture() == nullptr)
		weapon->SetTexture(texture);

	if (weapon->GetAnimation() != nullptr)
		weapon->GetAnimation()->SetTexture(texture);

	return weapon;
}

wstring ObjectManager::GetCursurImage(int num)
{
	wstring string;

	switch (num)
	{
	case 0:
		string = L"Resource/Cursur/BasicCursor.png";
		break;
	case 1:
		string = L"Resource/Cursur/ShootingCursor1.png";
		break;
	case 2:
		string = L"Resource/Cursur/ShootingCursor2.png";
		break;
	default:
		break;
	}

	return string;
}

wstring ObjectManager::GetNumberImage(int num)
{
	wstring string;

	switch (num)
	{
	case 0:
		string = L"Resource/Number/Zero.png";
		break;
	case 1:
		string = L"Resource/Number/One.png";
		break;
	case 2:
		string = L"Resource/Number/Two.png";
		break;
	case 3:
		string = L"Resource/Number/Three.png";
		break;
	case 4:
		string = L"Resource/Number/Four.png";
		break;
	case 5:
		string = L"Resource/Number/Five.png";
		break;
	case 6:
		string = L"Resource/Number/Six.png";
		break;
	case 7:
		string = L"Resource/Number/Seven.png";
		break;
	case 8:
		string = L"Resource/Number/Eight.png";
		break;
	case 9:
		string = L"Resource/Number/Nine.png";
		break;
	default:
		break;
	}

	return string;
}
