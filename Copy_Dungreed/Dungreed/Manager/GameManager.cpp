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
	for (auto& objects : _objects)
	{
		for (auto& object : objects)
		{
			object->Render();
		}
	}
}

void GameManager::PostRender()
{
	for (auto& objects : _objects)
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

shared_ptr<Player> GameManager::GetPlayer()
{
	return dynamic_pointer_cast<Player>(_objects[Object::Object_Type::CREATURE].back());
}

vector<shared_ptr<Object>> GameManager::GetCollisions(shared_ptr<Collider> collider, Object::Object_Type type)
{
	vector<shared_ptr<Object>> result;

	for (auto& i : _objects[type])
	{
		if (collider->IsCollision(i->GetCollider()))
		{
			i->GetCollider()->SetColorRed();
			result.emplace_back(i);
		}
	}

	return result;
}