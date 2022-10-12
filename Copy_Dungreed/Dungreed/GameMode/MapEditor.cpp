#include "framework.h"
#include "MapEditor.h"

MapEditor::MapEditor()
{
	GAME->Reset();
	_modeType = MAP_EDITOR;

	_map = MAP_MANAGER->Load(_mapLevel,_mapNum);
	GAME->SetMap(_map);
	GAME->GetPlaying() = false;

	_curObject = MAKE_OBJECT(_objectType, _objectLevel, _objectNum);
	CAMERA->SetTarget(nullptr);

	_mouseOffset.x = (_curObject->GetObjectTexture()->GetSize().x * _curObject->GetObjectTexture()->GetTransform()->GetScale().x);
	_mouseOffset.y = (_curObject->GetObjectTexture()->GetSize().y * _curObject->GetObjectTexture()->GetTransform()->GetScale().y);

	MOUSE_CURSUR->CursurOn();
}

void MapEditor::Update()
{
	MouseEvenet();

	InputEvent();

	ApplyChange();

	GAME->Update();

	_curObject->Update();
}

void MapEditor::PreRender()
{
}

void MapEditor::Render()
{
	GAME->Render();

	_curObject->Render();
}

void MapEditor::PostRender()
{
	GAME->PostRender();

	_curObject->PostRender();

	{
		shared_ptr<Collider> temp = make_shared<RectCollider>(Vector2(40.0f, 40.0f));
		temp->GetPos() = _map->GetLeftBottom();
		temp->Update();
		temp->SetColorRed();
		temp->Render();

		temp = make_shared<RectCollider>(Vector2(40.0f, 40.0f));
		temp->GetPos() = _map->GetRightTop();
		temp->Update();
		temp->SetColorRed();
		temp->Render();

		temp = make_shared<RectCollider>(Vector2(20.0f, 20.0f));
		temp->GetPos() = _map->GetStartPos();
		temp->Update();
		temp->SetColorGreen();
		temp->Render();

		temp = make_shared<RectCollider>(_verticalDoorHalfSize);
		temp->GetPos() = _map->GetLeftDoor();
		temp->Update();
		temp->SetColorGreen();
		temp->Render();

		temp = make_shared<RectCollider>(_verticalDoorHalfSize);
		temp->GetPos() = _map->GetRightDoor();
		temp->Update();
		temp->SetColorGreen();
		temp->Render();

		temp = make_shared<RectCollider>(_horizonialDoorHalfSize);
		temp->GetPos() = _map->GetTopDoor();
		temp->Update();
		temp->SetColorGreen();
		temp->Render();

		temp = make_shared<RectCollider>(_horizonialDoorHalfSize);
		temp->GetPos() = _map->GetBottomDoor();
		temp->Update();
		temp->SetColorGreen();
		temp->Render();
	}
}

void MapEditor::ImGuiRender()
{
	if (ImGui::CollapsingHeader("MapEditor"))
	{
		if (CAMERA->GetFreeMode())
			ImGui::Text("FreeMode");
		else
			ImGui::Text("EditMode");

		ImGui::Text("Mouse Mode :");
		ImGui::SameLine();

		if (_freeMode)
			ImGui::Text("Unapply Offset");	
		else
			ImGui::Text("Apply Offset");

		if (ImGui::TreeNode("Object"))
		{
			ImGui::Text("Object Count : %d", _map->GetObjectCount());
			ImGui::SliderInt("Level", &_objectLevel, 0, 8);
			ImGui::SliderInt("Num", &_objectNum, 0, 99);
			ImGui::SliderInt("Type", &_objectType, 0, 3);

			if (ImGui::Button("Reverse"))
				_curObject->ReverseTexture();
		
			ImGui::Text("Object Type :");
			ImGui::SameLine();

			switch (_objectType)
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
			default:
				break;
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Mouse Offset"))
		{
			if (ImGui::Button("Apply Offset"))
				ApplyOffset();

			ImGui::SameLine();
			if (ImGui::Button("Reset Offset"))
				ResetOffset();

			if (ImGui::TreeNode("Append Offset As"))
			{
				if (ImGui::Button("Top"))
					_mouseAppend.y += _curObject->GetObjectTexture()->Top() - _curObject->GetObjectTexture()->GetTransform()->GetPos().y;

				ImGui::SameLine();
				if (ImGui::Button("Bottom"))
					_mouseAppend.y += _curObject->GetObjectTexture()->Bottom() - _curObject->GetObjectTexture()->GetTransform()->GetPos().y;

				ImGui::SameLine();
				if (ImGui::Button("Left"))
					_mouseAppend.x += _curObject->GetObjectTexture()->Left() - _curObject->GetObjectTexture()->GetTransform()->GetPos().x;

				ImGui::SameLine();
				if (ImGui::Button("Right"))
					_mouseAppend.x += _curObject->GetObjectTexture()->Right() - _curObject->GetObjectTexture()->GetTransform()->GetPos().x;

				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Map"))
		{
			ImGui::SliderInt("Level", &_mapLevel, 0, 8);
			ImGui::SliderInt("Num", &_mapNum, 0, 30);

			if (ImGui::Button("Save"))
				MAP_MANAGER->Save(_map);

			ImGui::SameLine();
			if (ImGui::Button("Load"))
			{
				_map = MAP_MANAGER->Load(_mapLevel, _mapNum);
				GAME->SetMap(_map);
				CAMERA->GetTransform()->GetPos() = (_map->GetStartPos() - CENTER) * -1;
			}

			ImGui::SameLine();
			if (ImGui::Button("Reset"))
				_map->Reset();

			if (ImGui::Button("Copy"))
				_copyMap = _map;

			ImGui::SameLine();
			if (ImGui::Button("Paste"))
			{
				if (_copyMap != nullptr)
				{
					_map->Paste(_copyMap);
					CAMERA->GetTransform()->GetPos() = (_map->GetStartPos() - CENTER) * -1;
				}
			}

			ImGui::Checkbox("AutoSave", &_autoSave);
			ImGui::SameLine();
			
			if (ImGui::Button("Save All"))
				MAP_MANAGER->SaveAll();

			if (ImGui::TreeNode("Reset Door"))
			{
				if (ImGui::Button("Left"))
					_map->GetLeftDoor() = Vector2(0, 0);
				ImGui::SameLine();

				if (ImGui::Button("Right"))
					_map->GetRightDoor() = Vector2(0, 0);
				ImGui::SameLine();

				if (ImGui::Button("Top"))
					_map->GetTopDoor() = Vector2(0, 0);
				ImGui::SameLine();

				if (ImGui::Button("Bottom"))
					_map->GetBottomDoor() = Vector2(0, 0);

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
	}
	GAME->ImguiRender();
}

void MapEditor::AddObject(const bool& toFront)
{
	_map->AddObject(_curObject, _objectType, toFront);
	_curObject = MAKE_OBJECT(_objectType, _objectLevel, _objectNum);

	if(_autoSave)
		MAP_MANAGER->Save(_map);
}

void MapEditor::DeleteObject(const bool& toFront)
{
	_map->DeleteObject(_curMousePos, _objectType, toFront);

	if (_autoSave)
		MAP_MANAGER->Save(_map);
}

void MapEditor::MouseEvenet()
{
	if (_freeMode == false)
	{
		_curMousePos.x = (int)MOUSE_WORLD_POS.x - ((int)MOUSE_WORLD_POS.x % (int)_mouseOffset.x) + (_mouseOffset.x / 2);
		_curMousePos.x += _mouseAppend.x;
		_curMousePos.y = (int)MOUSE_WORLD_POS.y - ((int)MOUSE_WORLD_POS.y % (int)_mouseOffset.y) + (_mouseOffset.y / 2);
		_curMousePos.y += _mouseAppend.y;
	}
	else
		_curMousePos = MOUSE_WORLD_POS;

	_curObject->GetObjectTexture()->GetTransform()->GetPos() = _curMousePos;
}

void MapEditor::InputEvent()
{	
	if (CAMERA->GetFreeMode() == false)
	{
		if (KEY_DOWN('Q'))
			AddObject(true);

		if (KEY_DOWN('W'))
			AddObject(false);

		if (KEY_PRESS('E'))
			AddObject(false);

		if (KEY_DOWN('A'))
			DeleteObject(true);

		if (KEY_DOWN('S'))
			DeleteObject(false);

		if (KEY_PRESS('D'))
			DeleteObject(false);

		if (KEY_DOWN('F'))
			SwitchBool(_freeMode);

		if (KEY_DOWN('Z'))
			_map->GetLeftBottom() = _curObject->GetObjectTexture()->GetTransform()->GetPos();

		if (KEY_DOWN('X'))
			_map->GetRightTop() = _curObject->GetObjectTexture()->GetTransform()->GetPos();

		if (KEY_DOWN('C'))
			_map->GetStartPos() = _curMousePos;

		if (KEY_DOWN(VK_UP))
			++_objectLevel;

		if (KEY_DOWN(VK_DOWN))
			--_objectLevel;

		if (KEY_DOWN(VK_RIGHT))
			++_objectNum;

		if (KEY_DOWN(VK_LEFT))
			--_objectNum;

		if (KEY_DOWN('J'))
		{
			_map->GetLeftDoor().x = _curObject->GetObjectTexture()->GetTransform()->GetPos().x;
			_map->GetLeftDoor().y = _curObject->GetObjectTexture()->GetTransform()->GetPos().y + _verticalDoorHalfSize.y;
			if (_autoSave)
				MAP_MANAGER->Save(_map);
		}

		if (KEY_DOWN('K'))
		{
			_map->GetBottomDoor().x = _curObject->GetObjectTexture()->GetTransform()->GetPos().x;
			_map->GetBottomDoor().y = _curObject->GetObjectTexture()->GetTransform()->GetPos().y;

			if (_autoSave)
				MAP_MANAGER->Save(_map);
		}


		if (KEY_DOWN('L'))
		{
			_map->GetRightDoor().x = _curObject->GetObjectTexture()->GetTransform()->GetPos().x;
			_map->GetRightDoor().y = _curObject->GetObjectTexture()->GetTransform()->GetPos().y + _verticalDoorHalfSize.y;
			if (_autoSave)
				MAP_MANAGER->Save(_map);
		}

		if (KEY_DOWN('I'))
		{
			_map->GetTopDoor().x = _curObject->GetObjectTexture()->GetTransform()->GetPos().x;
			_map->GetTopDoor().y = _curObject->GetObjectTexture()->GetTransform()->GetPos().y;			
			if (_autoSave)
				MAP_MANAGER->Save(_map);
		}

	}

	if (KEY_DOWN('G'))
		SwitchBool(CAMERA->GetFreeMode());
	
}

void MapEditor::ApplyOffset()
{

	_mouseOffset.x = _curObject->GetObjectTexture()->GetSize().x * _curObject->GetObjectTexture()->GetTransform()->GetScale().x;
	_mouseOffset.y = _curObject->GetObjectTexture()->GetSize().y * _curObject->GetObjectTexture()->GetTransform()->GetScale().y;
}

void MapEditor::ApplyChange()
{
	if (_curObject->GetType() != _objectType || _curObject->GetLevel() != _objectLevel || _curObject->GetNum() != _objectNum)
	{
		if (_objectNum < 0)
			_objectNum = 0;

		if (_objectLevel < 0)
			_objectLevel = 0;

		_curObject = MAKE_OBJECT(_objectType, _objectLevel, _objectNum);
	}
}

void MapEditor::ResetOffset()
{
	_mouseOffset = { 1,1 };
	_mouseAppend = { 0,0 };
}
