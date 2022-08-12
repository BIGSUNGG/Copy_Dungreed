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
	if (_renderCollider)
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
	ImGui::SliderInt("Render Collider", &_renderCollider, 0, 1);
}

void GameManager::Optimize()
{
	for (auto& object : _objects[Object::EFFECT])
	{
		if (object == nullptr)
			continue;

		if (object->GetAnimation()->GetIsPlaying() == false)
		{
			object = nullptr;
		}
	}

	shared_ptr<Collider> temp = make_shared<RectCollider>(CENTER);
	temp->GetPos() = CAMERA->GetPos() + CENTER;
	temp->Update();

	_optimized.clear();

	_optimized.emplace_back(GetCollisions(temp, Object::BACKGROUND, false));
	
	_optimized.emplace_back(GetCollisions(temp, Object::WALL, false));
	
	_optimized.emplace_back(GetCollisions(temp, Object::TILE, false));
	
	_optimized.emplace_back(GetCollisions(temp, Object::CREATURE, false));
	
	_optimized.emplace_back(GetCollisions(temp, Object::EFFECT, false));
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

vector<shared_ptr<Object>> GameManager::GetCollisions(shared_ptr<Collider> collider, Object::Object_Type type,bool setColor)
{
	vector<shared_ptr<Object>> result;

	for (auto& object : _objects[type])
	{
		if (object == nullptr)
			continue;

		if (collider->IsCollision(object->GetCollider()))
		{
			if(setColor == true)
				object->GetCollider()->SetColorRed();
			result.emplace_back(object);
		}
	}

	return result;
}