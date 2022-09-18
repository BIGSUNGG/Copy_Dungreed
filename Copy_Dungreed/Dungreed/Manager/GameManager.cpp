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

	for (auto& objects : _optimized)
	{
		for (auto& object : objects)
		{
			if (object == nullptr)
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
	if (_renderCollider == false)
		return;

	for (auto& objects : _optimized)
	{
		for (auto& object : objects)
		{
			if (object == nullptr)
				continue;

			object->PostRender();
		}
	}
}

void GameManager::ImguiRender()
{
	for (auto& objects : _optimized)
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

	_optimized.clear();

	_optimized.emplace_back(GetCollisions(temp, Object::BACKGROUND, false, false));
	
	_optimized.emplace_back(GetCollisions(temp, Object::WALL, false, false));
	
	_optimized.emplace_back(GetCollisions(temp, Object::TILE, false, false));
	
	_optimized.emplace_back(GetCollisions(temp, Object::CREATURE, false, false));
	
	_optimized.emplace_back(GetCollisions(temp, Object::ECT, false, false));

	_optimized.emplace_back(GetCollisions(temp, Object::EFFECT, false, false));
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
		_player->Death();

	_player = player;
	_curMap->GetObjects()[Object::Object_Type::CREATURE].emplace_back(player);
}

void GameManager::AddEctObject(shared_ptr<Object> object)
{
	AddObject(object, Object::Object_Type::ECT, false);
}

vector<shared_ptr<Object>> GameManager::GetCollisions(shared_ptr<Collider> collider, Object::Object_Type type,bool Obb,bool setColor)
{
	vector<shared_ptr<Object>> result;
	collider->Update();

	for (auto& object : _curMap->GetObjects()[type])
	{
		if (object == nullptr || collider == object->GetCollider())
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
