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
	if (DELTA_TIME >= _maxDeltaTime)
		return;

	Input();

	if (!_pause)
	{
		for (auto& objects : _curMap->GetObjects())
		{
			for (auto& object : objects)
			{
				if (object == nullptr)
					continue;

				if (object->IsStatic() == true)
				{
					object->GetCollider()->SetColorGreen();
					continue;
				}
				object->Update();
			}
		}
		_curMap->CheckCleared();
		Optimize();

		for (auto& debug : _debugCollider)
			debug.second -= DELTA_TIME;
	}


	_curMap->CheckCleared();

	MAP_MANAGER->Update();

	if (_enableUI)
		UI_MANAGER->Update();
}

void GameManager::PreRender()
{
	if (_enableUI && _renderUI)
		UI_MANAGER->PreRender();
}

void GameManager::Render()
{
	if (_renderTexture == false)
		return;

	if (_renderTexture == false)
		return;

	shared_ptr<RectCollider> frustumCollision = make_shared<RectCollider>(CENTER * _frustumSizeRatio);
	frustumCollision->GetPos() = CAMERA->GetPos() + CENTER;
	frustumCollision->Update();

	shared_ptr<RectCollider> textureCollider = make_shared<RectCollider>(CENTER);

	if (_instancing)
	{
		for (auto& map : _renderOrder)
		{
			for (auto& instance : map.second.second)
			{
				// 인스턴스된 텍스쳐의 프러스텀 컬링
				textureCollider->SetHalfSize(instance->GetTexture()->GetHalfSize());
				for (shared_ptr<Transform> transform : instance->GetTransforms())
				{
					if (transform == nullptr)
						continue;

					// 텍스쳐가 화면안에 들어와 있는지
					textureCollider->GetTransform()->GetPos() = transform->GetWorldPos();
					textureCollider->GetTransform()->GetScale() = transform->GetWorldScale();
					textureCollider->GetTransform()->GetAngle() = transform->GetAngle();
					textureCollider->Update();

					if (frustumCollision->IsCollision(textureCollider, false))
					{
						instance->Render();
						break;
					}
				}
			}

			for (auto& object : map.second.first)
			{
				if (object == nullptr || object->IsActive() == false)
					continue;

				bool bShouldRender = true;
				if (_instancing)
				{
					// 오브젝트의 프러스텀 컬링
					shared_ptr<Transform> transform = object->GetObjectTexture() == nullptr ? nullptr : object->GetObjectTexture()->GetTransform();
					if (transform != nullptr)
					{
						// 텍스쳐가 화면안에 들어와 있는지
						textureCollider->SetHalfSize(object->GetObjectTexture()->GetHalfSize());
						textureCollider->GetTransform()->GetPos() = transform->GetWorldPos();
						textureCollider->GetTransform()->GetScale() = transform->GetWorldScale();
						textureCollider->GetTransform()->GetAngle() = transform->GetAngle();
						textureCollider->Update();

						bShouldRender = frustumCollision->IsCollision(textureCollider, false);
					}
				}

				if (bShouldRender)
					object->Render();
			}
		}
	}
	else
	{
		for (auto& objects : _curMap->GetObjects())
		{
			for (auto& object : objects)
			{
				if (object == nullptr || object->IsActive() == false)
					continue;

				bool bShouldRender = true;

				// 오브젝트의 프러스텀 컬링
				shared_ptr<Transform> transform = object->GetObjectTexture() == nullptr ? nullptr : object->GetObjectTexture()->GetTransform();
				if (transform != nullptr)
				{
					// 텍스쳐가 화면안에 들어와 있는지
					textureCollider->SetHalfSize(object->GetObjectTexture()->GetHalfSize());
					textureCollider->GetTransform()->GetPos() = transform->GetWorldPos();
					textureCollider->GetTransform()->GetScale() = transform->GetWorldScale();
					textureCollider->GetTransform()->GetAngle() = transform->GetAngle();
					textureCollider->Update();

					bShouldRender = frustumCollision->IsCollision(textureCollider, false);
				}

				if (bShouldRender)
					object->Render();
			}
		}
	}
}

void GameManager::PostRender()
{
	if (_renderCollider)
	{
		shared_ptr<RectCollider> frustumCollision = make_shared<RectCollider>(CENTER * _frustumSizeRatio);
		frustumCollision->GetPos() = CAMERA->GetPos() + CENTER;
		frustumCollision->Update();

		shared_ptr<RectCollider> textureCollider = make_shared<RectCollider>(CENTER);

		for (int i = Object::TILE; i < Object::EFFECT; i++)
		{
			const vector<shared_ptr<Object>>& objects = _curMap->GetObjects()[i];
			for (auto& object : objects)
			{
				if (object == nullptr)
					continue;

				bool bShouldRender = true;

				shared_ptr<Transform> transform = object->GetObjectTexture() == nullptr ? nullptr : object->GetObjectTexture()->GetTransform();
				if (transform)
				{
					// 텍스쳐가 화면안에 들어와 있는지
					textureCollider->SetHalfSize(object->GetObjectTexture()->GetHalfSize());
					textureCollider->GetTransform()->GetPos() = transform->GetWorldPos();
					textureCollider->GetTransform()->GetScale() = transform->GetWorldScale();
					textureCollider->GetTransform()->GetAngle() = transform->GetAngle();
					textureCollider->Update();

					bShouldRender = frustumCollision->IsCollision(textureCollider, false);
				}

				if (bShouldRender)
					object->PostRender();
			}
		}

		for (auto& collider : _debugCollider)
		{
			if (collider.second > 0)
				collider.first->Render();
		}
	}

	if(_enableUI && _renderUI)
		UI_MANAGER->PostRender();
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
		ImGui::Checkbox("Render UI", &_renderUI);

		ImGui::Checkbox("Use Instancing", &_instancing);
		ImGui::SliderFloat("Frustum Size Ratio", &_frustumSizeRatio, 0.f, 1.f);

	}
}

void GameManager::Optimize()
{
	// 활성화되지 않은 오브젝트 제거
	for (auto& objects : _curMap->GetObjects())
	{
		for (auto& object : objects)
		{
			if (object == nullptr)
				continue;

			if (object->IsActive() == false)
				object = nullptr;
		}
	}
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
			if (object == nullptr || object->IsStatic() == false)
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
			UI_MANAGER->SetState(UIManager::UI_State::OPTION);
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

void GameManager::SetPlayer(shared_ptr<Player> player)
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

void GameManager::ResetPlayer()
{
	_player = nullptr;
}

void GameManager::AddEtcObject(shared_ptr<Object> object)
{
	AddObject(object, Object::Object_Type::ETC);
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
	if (deleteObject->IsStatic())
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

		if (object->GetCollider() == nullptr)
			continue;

		if (object->IsCollision() == false && forceCollison == false)
			continue;

		if (collider->IsCollision(object->GetCollider(), Obb))
		{
			if (setColor == true)
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
	for (auto& object : _curMap->GetObjects()[Object::ETC])
	{
		if(object == nullptr)
			continue;

		if (object->GetType() == Object::ETC)
		{
			auto temp = dynamic_pointer_cast<Etc>(object);
			if (temp->GetEtcType() == Etc::BULLET)
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
	for (auto& objects : _curMap->GetObjects())
	{
		for (auto& object : objects)
		{
			if (object == nullptr || object->IsStatic())
				continue;

			_renderOrder[object->GetRenderOrder()].first.emplace_back(object);
		}
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
