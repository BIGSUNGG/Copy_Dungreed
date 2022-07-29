#include "framework.h"
#include "MapEditor.h"

MapEditor::MapEditor()
{
	_map = make_shared<Map>();

	_curObject = make_shared<Tile>(_level,_type,1);
}

void MapEditor::Update()
{
	if (KEY_DOWN('R'))
	{
		if (_isPlaying == true)
			_isPlaying = false;
		else
			_isPlaying = true;
	}

	if (_isPlaying == false)
		return;

	MouseEvenet();

	KeyBoradEvenet();

	if (_level != _beforeLevel || _type != _beforeType || _num != _beforeNum ||
		_curType != _objectType)
	{
		_curObject = make_shared<Tile>(_level, _type, _num);
		_beforeLevel = _level;
		_beforeType = _type;
		_beforeNum = _num;
		switch (_curType)
		{
		case Map::BACKGROUND:
		{
			_objectType = Map::BACKGROUND;
			_curObject = make_shared<BackGround>(_level, _num);
		}
			break;
		case Map::TILE:
			_objectType = Map::TILE;
			break;
		case Map::BUILDING:
			_objectType = Map::BUILDING;
			break;
		case Map::CREATURE:
			_objectType = Map::CREATURE;
			break;
		case Map::EFFECT:
			_objectType = Map::EFFECT;
			break;
		default:
			break;
		}
	}
	_map->Update();

	_curObject->Update();
}

void MapEditor::PreRender()
{
}

void MapEditor::Render()
{
	_map->Render();
	
	_curObject->Render();
}

void MapEditor::PostRender()
{
	_map->PostRender();
}

void MapEditor::ImGuiRender()
{
	ImGui::Text("Count : %d", _countObject);
	ImGui::SliderInt("Level", &_level, 0, 8);
	ImGui::SliderInt("Type", &_type, 0, 7);
	ImGui::SliderInt("Num", &_num, 0, 7);
	ImGui::SliderInt("CurType", &_curType, 0, 4);
	switch (_objectType)
	{
	case Map::BACKGROUND:
		ImGui::Text("BACKGROUND");
		break;
	case Map::TILE:
		ImGui::Text("TILE");
		break;
	case Map::BUILDING:
		ImGui::Text("BUILDING");
		break;
	case Map::CREATURE:
		ImGui::Text("CREATURE");
		break;
	case Map::EFFECT:
		ImGui::Text("EFFECT");
		break;
	default:
		break;
	}
}

void MapEditor::MouseEvenet()
{
	if (_freeMode == false)
	{
		_curMousePos.x = (int)MOUSE_WORLD_POS.x - ((int)MOUSE_WORLD_POS.x % (int)(_curObject->GetTexture()->GetSize().x * _curObject->GetTexture()->GetTransform()->GetScale().x))
			+ (_curObject->GetTexture()->GetHalfSize().x * _curObject->GetTexture()->GetTransform()->GetScale().x);
		_curMousePos.y = (int)MOUSE_WORLD_POS.y - ((int)MOUSE_WORLD_POS.y % (int)(_curObject->GetTexture()->GetSize().y * _curObject->GetTexture()->GetTransform()->GetScale().y))
			+ (_curObject->GetTexture()->GetHalfSize().y * _curObject->GetTexture()->GetTransform()->GetScale().y);
	}
	else
	{
		_curMousePos = MOUSE_WORLD_POS;
	}
	_curObject->GetTexture()->GetTransform()->GetPos() = _curMousePos;
}

void MapEditor::KeyBoradEvenet()
{	
	if (KEY_DOWN('W'))
	{
		_map->AddObject(_curObject, _objectType);
		_curObject = make_shared<Tile>(_level, _type, _num);
	}
	if (KEY_PRESS('D'))
	{
		_map->DeleteObject(_curObject, _objectType);
	}
	if (KEY_DOWN('F'))
	{
		if (_freeMode == true)
			_freeMode = false;
		else
			_freeMode = true;
	}
}
