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
			object->Render();
		}
	}
}

void GameManager::PostRender()
{
	for (auto& objects : _optimized)
	{
		for (auto& object : objects)
		{
			object->PostRender();
		}
	}
}

void GameManager::ImguiRender()
{
}

void GameManager::Optimize()
{
	shared_ptr<Collider> temp = make_shared<RectCollider>(CENTER);
	temp->GetPos() = CAMERA->GetPos() + CENTER;
	temp->Update();

	_optimized.clear();

	_optimized.emplace_back(GetCollisions(temp, Object::BACKGROUND, false));

	_optimized.emplace_back(GetCollisions(temp, Object::WALL, false));

	_optimized.emplace_back(GetCollisions(temp, Object::TILE, false));

	_optimized.emplace_back(GetCollisions(temp, Object::CREATURE, false));

	_optimized.emplace_back(GetCollisions(temp, Object::EFFECT, false));

	_optimized.emplace_back(GetCollisions(temp, Object::UI, false));
}

vector<shared_ptr<Object>> GameManager::GetCollisions(shared_ptr<Collider> collider, Object::Object_Type type,bool setColor)
{
	vector<shared_ptr<Object>> result;

	for (auto& i : _objects[type])
	{
		if (collider->IsCollision(i->GetCollider()))
		{
			if(setColor == true)
				i->GetCollider()->SetColorRed();
			result.emplace_back(i);
		}
	}

	return result;
}