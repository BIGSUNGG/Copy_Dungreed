#include "framework.h"
#include "GameManager.h"

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
{
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
	
	for (auto& objects : _curMap->GetObjects())
	{
		for (auto& object : objects)
		{
			if (object == nullptr)
				continue;
			else if (object->GetInstance() == true)
			{
				object->GetCollider()->SetColorGreen();
				continue;
			}

			auto temp = objects;

			object->Update();
		}
	}
}

void GameManager::PreRender()
{
}

void GameManager::Render()
{
	if (_renderTexture == false)
		return;

	for (int i = Object::BACKGROUND; i < Object::UI; i++)
	{
		for (auto& instanceQuad : _instanceQuad[i])
		{
			instanceQuad->Render();
		}

		for (auto& object : _curMap->GetObjects()[i])
		{
			if (object == nullptr || object->GetInstance() == true)
				continue;

			object->Render();
		}
	}


	for (auto& collider : _debugCollider)
	{
		collider->Render();
	}
}

void GameManager::PostRender()
{
	if (_renderCollider)
	{
		for (int i = Object::TILE; i < Object::UI; i++)
		{
			for (auto& object : _curMap->GetObjects()[i])
			{
				if (object == nullptr)
					continue;

				object->PostRender();
			}
		}
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
	_objectInScreen.emplace_back(GetCollisions(temp, Object::CREATURE, false, false,true));	
	_objectInScreen.emplace_back(GetCollisions(temp, Object::ECT, false, false,true));
	_objectInScreen.emplace_back(GetCollisions(temp, Object::EFFECT, false, false,true));
}

void GameManager::Instancing()
{
	if (_curMap == nullptr)
		return;

	_instanceQuad.clear();
	_instanceQuad.resize(Object::_objectTypeCount);

	for (int i = 0; i < Object::Object_Type::CREATURE; i++)
	{
		unordered_map<wstring, vector<shared_ptr<Transform>>> _objects;
		for (auto& object : _curMap->GetObjects()[i])
		{
			if (object == nullptr || object->GetInstance() == false)
				continue;

			object->Update();
			_objects[object->GetObjectTexture()->GetImageFile()].emplace_back(object->GetObjectTexture()->GetTransform());
		}

		for (auto& iter : _objects)
		{
			auto instanceQuad = make_shared<InstanceQuad>(iter.first, iter.second.size());
			for (int j = 0; j < iter.second.size(); j++)
			{
				instanceQuad->GetTransforms()[j] = iter.second[j];
			}
			instanceQuad->ApplyChanges();
			_instanceQuad[i].emplace_back(instanceQuad);
		}
	}
}

void GameManager::Input()
{
	if (_player == nullptr)
		return;

	if (UI_MANAGER->GetCurState() == UIManager::UI_State::NOMAL)
	{
		if (KEY_DOWN('W'))
			_player->Jump();

		if (KEY_PRESS('S'))
		{
			if (KEY_DOWN(VK_SPACE))
				_player->SetPassFloor(true);
			else
				_player->SetPassFloor(false);
		}
		else if (KEY_UP('S'))
			_player->SetPassFloor(false);

		if (KEY_PRESS('A'))
			_player->MoveLeft();
		if (KEY_PRESS('D'))
			_player->MoveRight();
		if (KEY_PRESS(VK_LBUTTON))
			_player->Attack();
		if (KEY_DOWN(VK_RBUTTON))
			_player->Dash();

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
		case UIManager::UI_State::INVEN:
			UI_MANAGER->SetState(UIManager::UI_State::NOMAL);
			break;
		default:
			UI_MANAGER->SetState(UIManager::UI_State::NOMAL);
			break;
		}
	}

	if (KEY_DOWN(VK_TAB) && _curMap->GetCleared())
	{
		if (UI_MANAGER->GetCurState() == UIManager::UI_State::MAP)
		{
			UI_MANAGER->SetState(UIManager::UI_State::NOMAL);
		}
		else
		{
			UI_MANAGER->SetState(UIManager::UI_State::MAP);
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

	object->GetObjectTexture()->Update();
	object->GetCollider()->Update();
	_curMap->GetObjects()[type].emplace_back(object);
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

		if (collider->IsCollision(object->GetCollider(), Obb))
		{
			if(setColor == true)
				object->GetCollider()->SetColorRed();

			result.emplace_back(object);
		}
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
	_objectInScreen.clear();
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

	Instancing();

	CAMERA->SetLeftBottom(map->GetLeftBottom());
	CAMERA->SetRightTop(map->GetRightTop());

	UI_MANAGER->SetState(UIManager::UI_State::NOMAL);
}

void GameManager::Reset()
{
	_curMap = nullptr;
	_objectInScreen.clear();
	_debugCollider.clear();
	_player = nullptr;
}
