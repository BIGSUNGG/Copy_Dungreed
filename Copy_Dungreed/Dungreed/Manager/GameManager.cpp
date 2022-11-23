#include "framework.h"
#include "GameManager.h"

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
{
	_objectInScreen.resize(Object::_objectTypeCount);
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{
	if (DELTA_TIME >= _maxDelay)
		return;

	Optimize();
	Input();
	
	if (!_pause)
	{
		for (auto& objects : _curMap->GetObjects())
		{
			for (auto& object : objects)
			{
				if (object == nullptr)
					continue;

				if (object->GetStatic() == true)
				{
					object->GetCollider()->SetColorGreen();
					continue;
				}
				object->Update();
			}
		}
		_curMap->CheckCleared();

		for (auto& debug : _debugCollider)
			debug.second -= DELTA_TIME;
	}
}

void GameManager::PreRender()
{
}

void GameManager::Render()
{
	if (_renderTexture == false)
		return;

	for (auto& map : _renderOrder)
	{
		for (auto& instance : map.second.second)
			instance->Render();

		for (auto& object : map.second.first)
		{
			if(object == nullptr || object->GetIsActive() == false)
				continue;

			object->Render();
		}
	}
}

void GameManager::PostRender()
{
	if (_renderCollider == false)
		return;

	for (int i = Object::TILE; i < Object::EFFECT; i++)
	{
		for (auto& object : _objectInScreen[i])
		{
			if (object == nullptr)
				continue;

			object->PostRender();
		}
	}

	for (auto& collider : _debugCollider)
	{
		if(collider.second > 0)
			collider.first->Render();
	}
}

void GameManager::ImguiRender()
{
	for (auto& objects : _curMap->GetObjects())
	{
		for (auto& object : objects)
		{
			if (object == nullptr)
				continue;

			object->ImGuiRender();
		}
	}

	if (ImGui::CollapsingHeader("GameManager"))
	{
		ImGui::Checkbox("Pause", &_pause);
		ImGui::Checkbox("Render Texture", &_renderTexture);
		ImGui::Checkbox("Render Collider", &_renderCollider);
	}
}

void GameManager::Optimize()
{
	for (auto& objects : _curMap->GetObjects())
	{
		for (auto& object : objects)
		{
			if (object == nullptr)
				continue;

			if (object->GetIsActive() == false)
				object = nullptr;
		}
	}

	shared_ptr<Collider> temp = make_shared<RectCollider>(CENTER);
	temp->GetPos() = CAMERA->GetPos() + CENTER;
	temp->Update();

	_objectInScreen.clear();
	_objectInScreen.emplace_back(GetCollisions(temp, Object::BACKGROUND, false, false, true));
	_objectInScreen.emplace_back(GetCollisions(temp, Object::WALL, false, false, true));
	_objectInScreen.emplace_back(GetCollisions(temp, Object::TILE, false, false, true));
	_objectInScreen.emplace_back(GetCollisions(temp, Object::CREATURE, false, false, true));
	_objectInScreen.emplace_back(GetCollisions(temp, Object::ECT, false, false, true));
	_objectInScreen.emplace_back(GetCollisions(temp, Object::EFFECT, false, false, true));
}

void GameManager::Instancing()
{
	if (_curMap == nullptr)
		return;

	for (auto& map : _renderOrder)
	{
		map.second.second.clear();
	}

	for (int i = 0; i < Object::Object_Type::CREATURE; i++)
	{
		unordered_map<wstring, vector<shared_ptr<Object>>> _objects;
		for (auto& object : _curMap->GetObjects()[i])
		{
			if (object == nullptr || object->GetStatic() == false)
				continue;

			object->Update();
			_objects[object->GetObjectTexture()->GetImageFile()].emplace_back(object);
		}

		for (auto& iter : _objects)
		{
			auto instanceQuad = make_shared<InstanceQuad>(iter.first, iter.second.size());
			for (int j = 0; j < iter.second.size(); j++)
			{
				instanceQuad->GetTransforms()[j] = iter.second[j]->GetObjectTexture()->GetTransform();
			}
			instanceQuad->ApplyChanges();
			_renderOrder[iter.second.front()->GetRenderOrder()].second.emplace_back(instanceQuad);
		}
	}
}

void GameManager::Input()
{
	if (_player == nullptr || !_input)
		return;

	if (UI_MANAGER->GetCurState() == UIManager::UI_State::NOMAL)
	{
		if (KEY_DOWN('W'))
			_player->Jump();

		if (KEY_DOWN(VK_SPACE))
		{
			if (KEY_PRESS('S'))
				_player->SetPassFloor(true);
			else
				_player->Jump();
		}

		if (KEY_PRESS('A'))
			_player->MoveLeft();
		if (KEY_PRESS('D'))
			_player->MoveRight();
		if (KEY_PRESS(VK_LBUTTON))
			_player->Attack();
		if (KEY_DOWN(VK_RBUTTON))
			_player->Dash();
		if (KEY_DOWN('Q'))
			_player->Skill();
		if (KEY_DOWN('F'))
			_player->Interaction();

		_player->MouseEvent();
	}
	else if (UI_MANAGER->GetCurState() == UIManager::UI_State::MAP)
	{
		_player->MouseEvent();
	}
	if (KEY_DOWN('1'))
		_player->SetCurWeaponSlot(0);
	if (KEY_DOWN('2'))
		_player->SetCurWeaponSlot(1);

	if (KEY_DOWN(VK_ESCAPE))
	{
		switch (UI_MANAGER->GetCurState())
		{
		case UIManager::UI_State::OPTION:
			UI_MANAGER->SetState(UIManager::UI_State::NOMAL);
			break;
		case UIManager::UI_State::SETTING:
			UI_MANAGER->SetState(UIManager::UI_State::NOMAL);
			break;
		default:
			UI_MANAGER->SetState(UIManager::UI_State::OPTION);
			break;
		}
	}

	if (KEY_DOWN(VK_TAB) && _curMap->GetCleared())
	{
		switch (UI_MANAGER->GetCurState())
		{
		case UIManager::UI_State::NOMAL:
			UI_MANAGER->SetState(UIManager::UI_State::MAP);
			break;
		default:
			break;
		}
	}
	else if (KEY_UP(VK_TAB))
	{
		if (UI_MANAGER->GetCurState() == UIManager::UI_State::MAP)
		{
			UI_MANAGER->SetState(UIManager::UI_State::NOMAL);
		}
	}

	if (KEY_DOWN('V') && _curMap->GetCleared())
	{
		if (UI_MANAGER->GetCurState() == UIManager::UI_State::INVEN)
		{
			UI_MANAGER->SetState(UIManager::UI_State::NOMAL);
		}
		else
		{
			UI_MANAGER->SetState(UIManager::UI_State::INVEN);
		}
	}
}

void GameManager::AddObject(shared_ptr<Object> object, int type)
{
	if (_curMap == nullptr)
		return;

	_renderOrder[object->GetRenderOrder()].first.emplace_back(object);
	_curMap->AddObject(object, type);
}

void GameManager::AddEffect(shared_ptr<Effect> effect)
{
	AddObject(effect, Object::Object_Type::EFFECT);
}

void GameManager::AddPlayer(shared_ptr<Player> player)
{
	if (_player != nullptr && _curMap != nullptr)
	{
		for (auto& object : _curMap->GetObjects()[Object::CREATURE])
		{
			auto creature = dynamic_pointer_cast<Creature>(object);
			if (creature != nullptr && creature->GetCreatureType() == Creature::PLAYER)
			{
				object = nullptr;
			}
		}
	}

	_player = player;
	CAMERA->SetTarget(_player->GetObjectTexture()->GetTransform());

	AddObject(_player, Object::Object_Type::CREATURE);
}

void GameManager::AddEctObject(shared_ptr<Object> object)
{
	AddObject(object, Object::Object_Type::ECT);
}

void GameManager::AddDebugCollider(shared_ptr<Collider> collider)
{
	for (auto& debug : _debugCollider)
	{
		if (debug.second <= 0)
		{
			debug.first = collider;
			debug.second = _debugColliderRunTime;
			return;
		}
	}

	_debugCollider.emplace_back(pair<shared_ptr<Collider>, float>(collider, _debugColliderRunTime));
}

void GameManager::DeleteObject(shared_ptr<Object> deleteObject)
{
	if (deleteObject->GetStatic())
	{
		for (auto& instance : _renderOrder[deleteObject->GetRenderOrder()].second)
		{
			if (instance->GetTexture()->GetImageFile() == deleteObject->GetObjectTexture()->GetImageFile())
			{
				for (auto& transform : instance->GetTransforms())
				{
					if (transform->GetPos() == deleteObject->GetObjectTexture()->GetTransform()->GetPos())
					{
						transform->GetPos() = Vector2(-10000.f, -10000.f);
						instance->ApplyChanges();
						return;
					}
				}
			}
		}
	}
	else
	{
		for (auto& object : _renderOrder[deleteObject->GetRenderOrder()].first)
		{
			if (object == deleteObject)
			{
				object = nullptr;
				return;
			}
		}
	}
}

vector<shared_ptr<Object>> GameManager::GetCollisions(shared_ptr<Collider> collider, Object::Object_Type type,bool Obb,bool setColor,bool forceCollison)
{
	vector<shared_ptr<Object>> result;
	collider->Update();

	for (auto& object : _curMap->GetObjects()[type])
	{
		if (object == nullptr || collider == object->GetCollider())
			continue;

		if (object->GetCollision() == false && forceCollison == false)
			continue;

		if (object->GetCollider() != nullptr)
		{
			if (collider->IsCollision(object->GetCollider(), Obb))
			{
				if (setColor == true)
					object->GetCollider()->SetColorRed();

				result.emplace_back(object);
			}
		}
		else if(forceCollison)
			result.emplace_back(object);

	}

	return result;
}

vector<shared_ptr<Object>> GameManager::GetCollisions(Vector2 pos, Object::Object_Type type, bool setColor)
{
	vector<shared_ptr<Object>> result;

	for (auto& object : _curMap->GetObjects()[type])
	{
		if (object == nullptr)
			continue;

		if (object->GetCollider()->IsCollision(object->GetCollider()))
		{
			if (setColor == true)
				object->GetCollider()->SetColorRed();

			result.emplace_back(object);
		}
	}

	return result;
}

void GameManager::SetCurMap(shared_ptr<Map> map)
{
	_curMap = map;
	for (auto& object : _curMap->GetObjects()[Object::ECT])
	{
		if(object == nullptr)
			continue;

		if (object->GetType() == Object::ECT)
		{
			auto temp = dynamic_pointer_cast<Ect>(object);
			if (temp->GetEctType() == Ect::BULLET)
				object = nullptr;
		}
	}

	for (auto& object : _curMap->GetObjects()[Object::EFFECT])
	{
		if (object == nullptr)
			continue;

		if (object->GetType() == Object::EFFECT)
		{
			auto temp = dynamic_pointer_cast<Effect>(object);
			if (temp->GetEffectType() == Effect::DESTROY)
				object = nullptr;
		}
	}

	for (auto& objects : map->GetObjects())
	{
		for (auto& object : objects)
		{
			if (object == nullptr)
				continue;

			if (object->GetObjectTexture() != nullptr)
				object->GetObjectTexture()->Update();

			if (object->GetCollider() != nullptr)
				object->GetCollider()->Update();
		}
	}

	_renderOrder.clear();
	Instancing();
	for(auto& objects : _curMap->GetObjects())
		for (auto& object : objects)
		{
			if(object == nullptr || object->GetStatic())
				continue;

			_renderOrder[object->GetRenderOrder()].first.emplace_back(object);
		}

	CAMERA->SetLeftBottom(map->GetLeftBottom());
	CAMERA->SetRightTop(map->GetRightTop());

	UI_MANAGER->SetState(UIManager::UI_State::NOMAL);
}

void GameManager::Reset()
{
	_curMap = nullptr;
	_debugCollider.clear();
	_player = nullptr;
}
