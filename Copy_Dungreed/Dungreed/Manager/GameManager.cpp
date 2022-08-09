#include "framework.h"
#include "GameManager.h"

vector<vector<shared_ptr<Object>>>* GameManager::_objects = nullptr;
GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

shared_ptr<Player> GameManager::GetPlayer()
{
	vector<vector<shared_ptr<Object>>>& objects = *_objects;

	return dynamic_pointer_cast<Player>(objects[Object::Object_Type::CREATURE].back());
}

vector<shared_ptr<Object>> GameManager::GetCollisions(shared_ptr<Collider> collider, Object::Object_Type type)
{
	vector<shared_ptr<Object>> result;
	vector<vector<shared_ptr<Object>>>& objects = *_objects;
	
	for (auto& i : objects[type])
	{
		if (collider->IsCollision(i->GetCollider()))
		{
			i->GetCollider()->SetColorRed();
			result.emplace_back(i);
		}
	}

	return result;
}