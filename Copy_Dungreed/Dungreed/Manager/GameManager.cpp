#include "framework.h"
#include "GameManager.h"

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
{
	SOUND->Add("bgm", "Resource/Sound/Bgm/0.Town.wav");
	SOUND->Play("bgm");
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{
	if (DELTA_TIME >= _maxDelay)
		return;

	Optimize();
	
	for (auto& objects : _curMap->GetObjects())
	{
		for (auto& object : objects)
		{
			if (object == nullptr)
				continue;

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

void GameManager::AddObject(shared_ptr<Object> object, int type, bool toFront)
{
	if (toFront == false)
	{
		bool addEffect = false;

		for (auto iter = _curMap->GetObjects()[type].begin(); iter != _curMap->GetObjects()[type].end(); iter++)
		{
			if (iter->get() == nullptr)
			{
				_curMap->GetObjects()[type].emplace(iter, object);
				addEffect = true;
				break;
			}
		}

		if (addEffect == false)
			_curMap->GetObjects()[type].emplace_back(object);
	}
	else
		_curMap->GetObjects()[type].emplace(_curMap->GetObjects()[type].begin(), object);
}

void GameManager::AddEffect(shared_ptr<Effect> effect)
{
	AddObject(effect, Object::Object_Type::EFFECT, false);
}

void GameManager::AddPlayer(shared_ptr<Player> player)
{
	if (_player != nullptr)
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
	_curMap->GetObjects()[Object::Object_Type::CREATURE].emplace_back(player);
}

void GameManager::AddEctObject(shared_ptr<Object> object)
{
	AddObject(object, Object::Object_Type::ECT, false);
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

void GameManager::SetMap(shared_ptr<Map> addedMap)
{
	_curMap = addedMap;
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

	Instancing();
}

void GameManager::Reset()
{
	_curMap = nullptr;
	_objectInScreen.clear();
	_debugCollider.clear();
	_player = nullptr;
}
