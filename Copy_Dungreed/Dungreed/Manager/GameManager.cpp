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

	// 코어 객체 업데이트
	CAMERA->Update();
	SOUND->Update();
	MOUSE_CURSUR->Update();

	// 오브젝트 업데이트
	if (!_pause)
	{
		// 입력
		Input();

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
		Optimize();

		for (auto& debug : _drawCollider)
			debug.second -= DELTA_TIME;
	}

	// 맵 정보 업데이트
	MAP_MANAGER->Update();

	// UI 업데이트
	if (_enableUI)
		UI_MANAGER->Update();
}

void GameManager::PreRender()
{
	if (_enableUI && _enableRenderUI)
		UI_MANAGER->PreRender();
}

void GameManager::Render()
{
	if (_enableRenderTexture == false)
		return;

	if (_enableRenderTexture == false)
		return;

	// 프러스텀 컬링에 사용할 콜라이더
	shared_ptr<RectCollider> frustumCollision = make_shared<RectCollider>(CENTER * _frustumSizeRatio);
	frustumCollision->GetPos() = CAMERA->GetPos() + CENTER;
	frustumCollision->Update();

	shared_ptr<RectCollider> textureCollider = make_shared<RectCollider>(CENTER);

	for (int i = 0; i < Object::_objectTypeCount; i++)
	{
		if (_enableInstancing)
		{
			// 인스턴싱 텍스쳐 렌더링
			for (auto instanceQuad : instanceQuads[i])
			{
				if (instanceQuad.second == nullptr)
					continue;

				if (_enableFrustum) // 프러스텀 컬링이 활성화되어 있는 경우
				{
					// 오브젝트의 프러스텀 컬링
					for (shared_ptr<Transform> transform : instanceQuad.second->GetTransforms())
					{
						if (transform == nullptr)
							continue;

						// 텍스쳐가 화면안에 들어와 있는지
						textureCollider->SetHalfSize(instanceQuad.second->GetTexture()->GetHalfSize());
						textureCollider->GetTransform()->GetPos() = transform->GetWorldPos();
						textureCollider->GetTransform()->GetScale() = transform->GetWorldScale();
						textureCollider->GetTransform()->GetAngle() = transform->GetAngle();
						textureCollider->Update();

						if (frustumCollision->IsCollision(textureCollider, false))
						{
							instanceQuad.second->Render();
							break;
						}
					}
				}
				else // 프러스텀 컬링이 비활성화되어 있는 경우
				{
					instanceQuad.second->Render();
				}
			}
		}

		// 오브젝트 렌더링
		for (auto& object : _curMap->GetObjects()[i])
		{
			if (object == nullptr || object->IsActive() == false)
				continue;

			if (_enableInstancing && object->IsStatic())
				continue;

			bool bShouldRender = true;
			if (_enableFrustum)
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

				if (bShouldRender)
					object->Render();
			}
			else // 프러스텀 컬링이 비활성화되어 있는 경우
			{
				object->Render();
			}
		}
	}
}

void GameManager::PostRender()
{
	// 콜라이더 렌더링
	if (_enableRenderCollider)
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
				if (_enableFrustum)
				{
					// 오브젝트의 프러스텀 컬링
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
				}

				if (bShouldRender)
					object->PostRender();
			}
		}

		// 추가 콜라이더 렌더링
		for (auto& collider : _drawCollider)
		{
			if (collider.second > 0)
				collider.first->Render();
		}
	}

	// UI 렌더링
	if(_enableUI && _enableRenderUI)
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
		ImGui::Checkbox("Render Texture", &_enableRenderTexture);
		ImGui::Checkbox("Render Collider", &_enableRenderCollider);
		ImGui::Checkbox("Render UI", &_enableRenderUI);

		ImGui::Checkbox("Use Instancing", &_enableInstancing);
		ImGui::Checkbox("Use Frustum culling", &_enableFrustum);
		ImGui::SliderFloat("Frustum Size Ratio", &_frustumSizeRatio, 0.f, 1.f);
	}

	UI_MANAGER->ImGuiRender();
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

void GameManager::AddInstanceQuad(shared_ptr<Object> object)
{
	if (object->IsStatic() == false || object->GetObjectTexture() == nullptr)
		return;

	auto& instanceQuad = instanceQuads[object->GetType()];
	auto iter = instanceQuad.find(object->GetObjectTexture()->GetImageFile());
	if (iter == instanceQuad.end())
		iter = instanceQuad.insert({ object->GetObjectTexture()->GetImageFile(), make_shared<InstanceQuad>(object->GetObjectTexture()->GetImageFile(), 0) }).first;

	iter->second->GetTransforms().push_back(object->GetObjectTexture()->GetTransform());
	iter->second->Update();
}

void GameManager::DeleteInstanceQuad(shared_ptr<Object> object)
{
	if (object->IsStatic() == false || object->GetObjectTexture() == nullptr)
		return;

	auto& instanceQuad = instanceQuads[object->GetType()];
	auto iter = instanceQuad.find(object->GetObjectTexture()->GetImageFile());
	if (iter == instanceQuad.end())
		return;

	for (int i = 0; i < iter->second->GetTransforms().size(); i++)
	{
		if (iter->second->GetTransforms()[i] == object->GetObjectTexture()->GetTransform())
		{
			iter->second->GetTransforms().erase(iter->second->GetTransforms().begin() + i);
			iter->second->Update();
			break;
		}
	}
}

void GameManager::Input()
{
	if (_player == nullptr || !_enableInput)
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
	for (auto& debug : _drawCollider)
	{
		if (debug.second <= 0)
		{
			debug.first = collider;
			debug.second = _drawColliderTime;
			return;
		}
	}

	_drawCollider.emplace_back(pair<shared_ptr<Collider>, float>(collider, _drawColliderTime));
}

void GameManager::AddObject(shared_ptr<Object> object, int type)
{
	if (_curMap == nullptr || object == nullptr)
		return;

	_curMap->AddObject(object, type);

	if (object->IsStatic())
		AddInstanceQuad(object);
}

void GameManager::DeleteObject(shared_ptr<Object> object)
{
	if (_curMap == nullptr)
		return;

	_curMap->DeleteObject(object);
	
	if (object->IsStatic())
		DeleteInstanceQuad(object);
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

void GameManager::SetCurMap(shared_ptr<StageMap> map)
{
	instanceQuads.clear();
	instanceQuads.resize(Object::_objectTypeCount);

	_curMap = map;
	for (auto& object : _curMap->GetObjects()[Object::ETC])
	{
		if(object == nullptr)
			continue;

		if (object->GetType() == Object::ETC)
		{
			// 투사체 오브젝트 삭제
			auto etc = dynamic_pointer_cast<Etc>(object);
			if (etc->GetEtcType() == Etc::BULLET)
				object = nullptr;
		}
	}

	_curMap->GetObjects()[Object::EFFECT].clear();

	for (int i = 0; i < Object::_objectTypeCount; i++)
	{
		for (auto& object : _curMap->GetObjects()[i])
		{
			if (object == nullptr)
				continue;

			if (object->GetObjectTexture() != nullptr)
				object->GetObjectTexture()->Update();

			if (object->GetCollider() != nullptr)
				object->GetCollider()->Update();

			if (object->IsStatic())
				AddInstanceQuad(object);
		}
	}

	CAMERA->SetLeftBottom(map->GetLeftBottom());
	CAMERA->SetRightTop(map->GetRightTop());

	UI_MANAGER->SetState(UIManager::UI_State::NOMAL);
}

void GameManager::Reset()
{
	_curMap = nullptr;
	_drawCollider.clear();

	ResetPlayer();

	INVENTORY->Reset();
}
