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

	_deleteTempTime += DELTA_TIME;

	Optimize();
	
	for (auto& objects : _objects)
	{
		for (auto& object : objects)
		{
			if (object == nullptr)
				continue;

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

	for (auto& temp : _tempCollider)
		temp->Render();
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
	if (_deleteTempTime >= _deleteTempDelay)
	{
		_deleteTempTime = 0.0f;
		_tempCollider.clear();
	}

	for(auto& objects : _objects)
		for (auto& object : objects)
		{
			if (object == nullptr)
				continue;

			if (object->GetIsActive() == false)
			{
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
	
	_optimized.emplace_back(GetCollisions(temp, Object::EFFECT, false, false));
}

void GameManager::AddObject(shared_ptr<Object> object, int type, bool toFront)
{
	if (toFront == false)
		_objects[type].emplace_back(object);
	else
		_objects[type].emplace(_objects[type].begin(), object);
}

void GameManager::AddEffect(shared_ptr<Effect> effect)
{
	_objects[Object::Object_Type::EFFECT].emplace_back(effect);
}

void GameManager::AddTempCollider(shared_ptr<Collider> collider)
{
	_tempCollider.push_back(collider);
}

vector<shared_ptr<Object>> GameManager::GetCollisions(shared_ptr<Collider> collider, Object::Object_Type type,bool Obb,bool setColor)
{
	vector<shared_ptr<Object>> result;

	for (auto& object : _objects[type])
	{
		if (object == nullptr)
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