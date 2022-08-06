#include "framework.h"
#include "MapEditor.h"

MapEditor::MapEditor()
{
	_map = make_shared<Map>();

	_curObject = GET_OBJECT(_curType, _level, _num);
}

void MapEditor::Update()
{
	MouseEvenet();

	InputEvent();

	RefreshChange();

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
	
	_curObject->PostRender();
}

void MapEditor::ImGuiRender()
{
	ImGui::Text("Object Count : %d", _map->_objectCount);
	ImGui::SliderInt("Level", &_level, 0, 8);
	ImGui::SliderInt("Num", &_num, 0, 30);
	ImGui::SliderInt("CurType", &_curType, 0, 4);

	switch (_type)
	{
	case Object::Object_Type::BACKGROUND:
		ImGui::Text("BACKGROUND");
		break;
	case Object::Object_Type::WALL:
		ImGui::Text("WALL");
		break;
	case Object::Object_Type::TILE:
		ImGui::Text("TILE");
		break;
	case Object::Object_Type::CREATURE:
		ImGui::Text("CREATURE");
		break;
	case Object::Object_Type::EFFECT:
		ImGui::Text("EFFECT");
		break;
	default:
		break;
	}

	if (ImGui::Button("Save"))
	{
		_map->Save();
	}
	if (ImGui::Button("Load"))
	{
		_map->Load();
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

void MapEditor::InputEvent()
{	
	if (CAMERA->GetFreeMode() == false)
	{
		if (KEY_DOWN('W'))
		{
			_map->AddObject(_curObject, _type);
			_curObject = GET_OBJECT(_type, _level, _num);
		}
		if (KEY_PRESS('Q'))
		{
			_map->AddObject(_curObject, _type);
			_curObject = GET_OBJECT(_type, _level, _num);
		}
		if (KEY_DOWN('D'))
		{
			_map->DeleteObject(_curMousePos, _type);
		}
		if (KEY_PRESS('E'))
		{
			_map->DeleteObject(_curMousePos, _type);
		}
		if (KEY_DOWN('F'))
		{
			SwitchBool(_freeMode);
		}
		if (KEY_DOWN(VK_UP))
		{
			++_level;
		}
		if (KEY_DOWN(VK_DOWN))
		{
			--_level;
		}
		if (KEY_DOWN(VK_RIGHT))
		{
			++_num;
		}
		if (KEY_DOWN(VK_LEFT))
		{
			--_num;
		}
	}

	if (KEY_DOWN('G'))
	{
		SwitchBool(CAMERA->GetFreeMode());
	}
}

void MapEditor::RefreshChange()
{
	if (_level == _beforeLevel && _num == _beforeNum && _type == _curType)
		return;

	if (_num < 0)
		_num = 0;

	if (_level < 0)
		_level = 0;

	_beforeLevel = _level;
	_beforeNum = _num;
	_type = (Object::Object_Type)_curType;

	_curObject = GET_OBJECT(_curType, _level, _num);
}

