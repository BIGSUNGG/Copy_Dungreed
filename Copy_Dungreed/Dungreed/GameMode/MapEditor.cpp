#include "framework.h"
#include "MapEditor.h"

MapEditor::MapEditor()
	: MapEditor(1, 0)
{

}

MapEditor::MapEditor(int level, int num)
{
	_modeType = MAP_EDITOR;
	_mapLevel = level;
	_mapNum = num;

	shared_ptr<Map> _map = MAP_MANAGER->LoadMap(level, num);
	Init(_map);
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

	// 맵의 가장자리와 문 위치 표시
	{
		// 가장 자리
		shared_ptr<Collider> temp = make_shared<RectCollider>(Vector2(40.0f, 40.0f));
		temp->GetPos() = _curMap->GetLeftBottom();
		temp->Update();
		temp->SetColorRed();
		temp->Render();

		temp = make_shared<RectCollider>(Vector2(40.0f, 40.0f));
		temp->GetPos() = _curMap->GetRightTop();
		temp->Update();
		temp->SetColorRed();
		temp->Render();

		// 문 위치
		temp = make_shared<RectCollider>(Vector2(20.0f, 20.0f));
		temp->GetPos() = _curMap->GetStartPos();
		temp->Update();
		temp->SetColorGreen();
		temp->Render();

		temp = make_shared<RectCollider>(_verticalDoorHalfSize);
		temp->GetPos() = _curMap->GetLeftDoor();
		temp->Update();
		temp->SetColorGreen();
		temp->Render();

		temp = make_shared<RectCollider>(_verticalDoorHalfSize);
		temp->GetPos() = _curMap->GetRightDoor();
		temp->Update();
		temp->SetColorGreen();
		temp->Render();

		temp = make_shared<RectCollider>(_horizonialDoorHalfSize);
		temp->GetPos() = _curMap->GetTopDoor();
		temp->Update();
		temp->SetColorGreen();
		temp->Render();

		temp = make_shared<RectCollider>(_horizonialDoorHalfSize);
		temp->GetPos() = _curMap->GetBottomDoor();
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

		ImGui::Text("Left");
		if (_curMap->CanGoLeft())
		{
			ImGui::SameLine();
			ImGui::Text(" O ");
		}

		ImGui::Text("Right");
		if (_curMap->CanGoRight())
		{
			ImGui::SameLine();
			ImGui::Text(" O ");
		}

		ImGui::Text("Top");
		if (_curMap->CanGoTop())
		{
			ImGui::SameLine();
			ImGui::Text(" O ");
		}

		ImGui::Text("Bottom");
		if (_curMap->CanGoBottom())
		{
			ImGui::SameLine();
			ImGui::Text(" O ");
		}

		if (ImGui::TreeNode("Object"))
		{
			ImGui::Text("Object Count : %d", _curMap->GetObjectCount());
			ImGui::SliderInt("Level", &_objectLevel, 0, 8);
			ImGui::SliderInt("Num", &_objectNum, 0, 99);
			ImGui::SliderInt("Type", &_objectType, 0, Object::Object_Type::CREATURE);

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
			case Object::Object_Type::ETC:
				ImGui::Text("ECT");
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
			ImGui::SliderInt("Level", &_mapLevel, 0, 17);
			ImGui::SliderInt("Num", &_mapNum, 0, 30);

			if (ImGui::Button("Save"))
				MAP_MANAGER->Save(_curMap);

			ImGui::SameLine();
			if (ImGui::Button("Load"))
			{
				_curMap = MAP_MANAGER->LoadMap(_mapLevel, _mapNum);
				GAME->SetCurMap(_curMap);
				CAMERA->GetTransform()->GetPos() = (_curMap->GetStartPos() - CENTER) * -1;
			}

			ImGui::SameLine();
			if (ImGui::Button("Reset"))
			{
				_curMap->Reset();
			}

			if (ImGui::Button("Copy"))
				_copyMap = _curMap;

			ImGui::SameLine();
			if (ImGui::Button("Paste"))
			{
				if (_copyMap != nullptr)
				{
					_curMap->Paste(_copyMap);
					CAMERA->GetTransform()->GetPos() = (_curMap->GetStartPos() - CENTER) * -1;
					GAME->SetCurMap(_curMap);
				}
			}

			ImGui::Checkbox("AutoSave", &_autoSave);
			ImGui::SameLine();
			
			if (ImGui::Button("Save All"))
				MAP_MANAGER->SaveAll();

			if (ImGui::TreeNode("Reset Door"))
			{
				if (ImGui::Button("Left"))
					_curMap->GetLeftDoor() = Vector2(0, 0);
				ImGui::SameLine();

				if (ImGui::Button("Right"))
					_curMap->GetRightDoor() = Vector2(0, 0);
				ImGui::SameLine();

				if (ImGui::Button("Top"))
					_curMap->GetTopDoor() = Vector2(0, 0);
				ImGui::SameLine();

				if (ImGui::Button("Bottom"))
					_curMap->GetBottomDoor() = Vector2(0, 0);

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
	}
	GAME->ImguiRender();
}

void MapEditor::Init(shared_ptr<Map> editMap)
{
	// 게임 초기화
	GAME->Reset();
	GAME->SetPlaying(false);
	GAME->SetEnableUI(false);

	// 맵 설정
	_curMap = editMap;
	GAME->SetCurMap(_curMap);

	// 오브젝트 설정
	_curObject = MAKE_OBJECT(_objectType, _objectLevel, _objectNum);

	// 카메라 설정
	CAMERA->SetTarget(nullptr);
	CAMERA->GetTransform()->GetPos() = (_curMap->GetStartPos() - CENTER) * -1;

	// 마우스 설정
	_mouseOffset.x = (_curObject->GetObjectTexture()->GetSize().x * _curObject->GetObjectTexture()->GetTransform()->GetScale().x);
	_mouseOffset.y = (_curObject->GetObjectTexture()->GetSize().y * _curObject->GetObjectTexture()->GetTransform()->GetScale().y);
	MOUSE_CURSUR->CursurOn();

	// 소리 설정
	SOUND->StopAll();
}

void MapEditor::AddObject(bool force)
{
	if (force == false)
	{
		bool overlap = false;
		for (auto& object : _curMap->GetObjects()[_objectType])
		{
			if (object->GetPos() == _curObject->GetObjectTexture()->GetTransform()->GetPos())
			{
				overlap = true;
				break;
			}
		}

		if (overlap)
			return;
	}

	GAME->AddObject(_curObject, _objectType);
	_curObject = MAKE_OBJECT(_objectType, _objectLevel, _objectNum);

	if (_autoSave)
		MAP_MANAGER->Save(_curMap);
}

void MapEditor::DeleteObject()
{
	shared_ptr<Object> deleteObject;
	for (int i = 0 ; i < _curMap->GetObjects()[_objectType].size(); i++)
	{
		if (_curObject->GetCollider()->IsCollision(_curMap->GetObjects()[_objectType][i]->GetCollider()->GetWorldPos()))
		{
			deleteObject = _curMap->GetObjects()[_objectType][i];
			break;
		}
	}

	bool success = _curMap->DeleteObject(deleteObject, _objectType);

	if (success) 
	{
		if (_autoSave)
			MAP_MANAGER->Save(_curMap);
	
		GAME->DeleteObject(deleteObject);
	}
}

void MapEditor::MouseEvenet()
{
	if (_freeMode == false)
	{
		// 마우스 오프셋에 맞춰 오브젝트 위치 설정
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
			AddObject();

		if (KEY_PRESS('E'))
			AddObject();

		if (KEY_DOWN('S'))
			DeleteObject();

		if (KEY_PRESS('D'))
			DeleteObject();

		if (KEY_DOWN('R'))
		{
			// 마우스 위치에 있는 오브젝트로 복사
			for (auto& object : _curMap->GetObjects()[_objectType])
			{
				if (object->GetPos() == _curObject->GetPos())
				{
					_objectType = object->GetType();
					_objectLevel = object->GetLevel();
					_objectNum = object->GetNum();
				}
			}
		}

		if (KEY_DOWN('F'))
			SWITCH_BOOL(_freeMode);

		if (KEY_DOWN('Z'))
			_curMap->GetLeftBottom() = _curObject->GetObjectTexture()->GetTransform()->GetPos();

		if (KEY_DOWN('X'))
			_curMap->GetRightTop() = _curObject->GetObjectTexture()->GetTransform()->GetPos();

		if (KEY_DOWN('C'))
			_curMap->GetStartPos() = _curMousePos;

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
			_curMap->GetLeftDoor().x = _curObject->GetObjectTexture()->GetTransform()->GetPos().x;
			_curMap->GetLeftDoor().y = _curObject->GetObjectTexture()->GetTransform()->GetPos().y + _verticalDoorHalfSize.y;
			if (_autoSave)
				MAP_MANAGER->Save(_curMap);
		}

		if (KEY_DOWN('K'))
		{
			_curMap->GetBottomDoor().x = _curObject->GetObjectTexture()->GetTransform()->GetPos().x;
			_curMap->GetBottomDoor().y = _curObject->GetObjectTexture()->GetTransform()->GetPos().y;

			if (_autoSave)
				MAP_MANAGER->Save(_curMap);
		}


		if (KEY_DOWN('L'))
		{
			_curMap->GetRightDoor().x = _curObject->GetObjectTexture()->GetTransform()->GetPos().x;
			_curMap->GetRightDoor().y = _curObject->GetObjectTexture()->GetTransform()->GetPos().y + _verticalDoorHalfSize.y;
			if (_autoSave)
				MAP_MANAGER->Save(_curMap);
		}

		if (KEY_DOWN('I'))
		{
			_curMap->GetTopDoor().x = _curObject->GetObjectTexture()->GetTransform()->GetPos().x;
			_curMap->GetTopDoor().y = _curObject->GetObjectTexture()->GetTransform()->GetPos().y;			
			if (_autoSave)
				MAP_MANAGER->Save(_curMap);
		}

	}

	if (KEY_DOWN('G'))
		CAMERA->SetFreeMode(!CAMERA->GetFreeMode());
	
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
