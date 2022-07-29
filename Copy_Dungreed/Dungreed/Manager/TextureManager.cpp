#include "framework.h"
#include "TextureManager.h"

TextureManager* TextureManager::_instance = nullptr;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

shared_ptr<Quad> TextureManager::GetTileTexture(int level, int type, int num)
{
	shared_ptr<Quad> _texture;

	switch (level)
	{
	case Map::LEVEL_00:
	{
		switch (type)
		{
		case Tile::TOP:
			break;
		case Tile::BOTTOM:
			switch (num)
			{
			case 0:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_OneWay_0.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
				break;
			case 1:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_OneWay_1.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
				break;
			case 2:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_OneWay_2.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
				break;
			case 3:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/SecondFloor_OneWay_3.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
				break;
			case 4:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_TopCenter.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
				break;
			case 5:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_TopLeft.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			case 6:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_TopRight.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			case 7:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/TownBasic_1.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			default:
				break;
			}
			break;
		case Tile::LEFT:
			break;
		case Tile::LEFT_TOP:
			switch (num)
			{
			case 0:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_RightStair.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
				break;
			case 1:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_RightStair2.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			default:
				break;
			}
			break;
		case Tile::RIGHT:
			break;
		case Tile::RIGHT_TOP:
			switch (num)
			{
			case 0:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_LeftStair.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			case 1:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_00/Tile/Town_LeftStair2.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
		break;
	case Map::LEVEL_01:
	{
		switch (type)
		{
		case Tile::TOP:
			break;
		case Tile::BOTTOM:
			switch (num)
			{
			case 0:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Basic_H_Type2_0.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			case 1:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Basic_H_Type2_1.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			case 2:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Basic_H_Type2_2.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			case 3:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopCenter_0.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			case 4:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopCenter_7.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			case 5:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/BasicStone_TopCenter_8.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			}
			break;
		case Tile::LEFT:
			break;
		case Tile::LEFT_TOP:
			switch (num)
			{
			case 0:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Marble_Stair_TopLeft.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			case 1:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Marble_Stair_BottomLeft.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			default:
				break;
			}
			break;
		case Tile::RIGHT:
			break;
		case Tile::RIGHT_TOP:
			switch (num)
			{
			case 0:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Marble_Stair_TopRight.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			case 1:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Marble_Stair_BottomRight.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
		break;
	case Map::LEVEL_02:
	{
		switch (type)
		{
		case Tile::TOP:
			break;
		case Tile::BOTTOM:
			switch (num)
			{
			case 0:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Marble_Stair_TopLeft.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			case 1:
			{
				_texture = make_shared<Quad>(L"Resource/Map/Level_01/Tile/Tile_Marble_Stair_BottomLeft.png");
				_texture->GetTransform()->GetScale() *= 3;
			}
			break;
			default:
				break;
			}
			break;
		case Tile::LEFT:
			break;
		case Tile::LEFT_TOP:
			break;
		case Tile::RIGHT:
			break;
		case Tile::RIGHT_TOP:
			break;
		default:
			break;
		}
	}
		break;
	case Map::LEVEL_03:
	{
		switch (type)
		{
		case Tile::TOP:
			break;
		case Tile::BOTTOM:
			break;
		case Tile::LEFT:
			break;
		case Tile::LEFT_TOP:
			break;
		case Tile::RIGHT:
			break;
		case Tile::RIGHT_TOP:
			break;
		default:
			break;
		}
	}
		break;
	case Map::LEVEL_04:
	{
		switch (type)
		{
		case Tile::TOP:
			break;
		case Tile::BOTTOM:
			break;
		case Tile::LEFT:
			break;
		case Tile::LEFT_TOP:
			break;
		case Tile::RIGHT:
			break;
		case Tile::RIGHT_TOP:
			break;
		default:
			break;
		}
	}
		break;
	case Map::LEVEL_05:
	{
		switch (type)
		{
		case Tile::TOP:
			break;
		case Tile::BOTTOM:
			break;
		case Tile::LEFT:
			break;
		case Tile::LEFT_TOP:
			break;
		case Tile::RIGHT:
			break;
		case Tile::RIGHT_TOP:
			break;
		default:
			break;
		}
	}
		break;
	case Map::LEVEL_06:
	{
		switch (type)
		{
		case Tile::TOP:
			break;
		case Tile::BOTTOM:
			break;
		case Tile::LEFT:
			break;
		case Tile::LEFT_TOP:
			break;
		case Tile::RIGHT:
			break;
		case Tile::RIGHT_TOP:
			break;
		default:
			break;
		}
	}
		break;
	case Map::LEVEL_07:
	{
		switch (type)
		{
		case Tile::TOP:
			break;
		case Tile::BOTTOM:
			break;
		case Tile::LEFT:
			break;
		case Tile::LEFT_TOP:
			break;
		case Tile::RIGHT:
			break;
		case Tile::RIGHT_TOP:
			break;
		default:
			break;
		}
	}
		break;
	case Map::PUBLIC:
	{
		switch (type)
		{
		case Tile::TOP:
			break;
		case Tile::BOTTOM:
			break;
		case Tile::LEFT:
			break;
		case Tile::LEFT_TOP:
			break;
		case Tile::RIGHT:
			break;
		case Tile::RIGHT_TOP:
			break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}

	if (_texture == nullptr)
		_texture = make_shared<Quad>(L"Resource/Ui/MainLogo.png");

	return _texture;
}

shared_ptr<Quad> TextureManager::GetBackGroundTexture(int level, int num)
{
	shared_ptr<Quad> _texture;

	switch (level)
	{
	case Map::LEVEL_00:
		switch (num)
		{
		case 0:
		{
			_texture = make_shared<Quad>(L"Resource/BackGround/Sky_Day.png");
			_texture->GetTransform()->GetScale() *= 3;
		}
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

	return _texture;
}

