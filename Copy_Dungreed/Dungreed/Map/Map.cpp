#include "framework.h"
#include "Map.h"

Map::Map()
{
	_objects.resize(6);
}

void Map::AddObject(shared_ptr<Object> addObject, Type type)
{
	for (auto& objects : _objects)
	{
		for (auto& object : objects)
		{
			if (object->GetTexture()->GetTransform()->GetPos() ==
				addObject->GetTexture()->GetTransform()->GetPos())
			{
				return;;
			}
		}
	}
	
	if(addObject->GetCollider() != nullptr )
		addObject->GetCollider()->Update();

	_objects[type].push_back(make_shared<Object>());
	_objects[type].back() = addObject;

}

void Map::DeleteObject(shared_ptr<Object> deleteObject, Type type)
{
	for (auto iter = _objects[type].begin(); iter != _objects[type].end(); iter++)
	{
		if (iter->get()->GetTexture()->GetTransform()->GetPos() ==
			deleteObject->GetTexture()->GetTransform()->GetPos())
		{
			iter = _objects[type].erase(iter);
			break;
		}
	}
}

void Map::Update()
{
	for (auto& objects : _objects)
	{
		for (auto& object : objects)
		{
			object->Update();
		}
	}
}

void Map::PreRender()
{
}

void Map::Render()
{
	int temp = 0;
	for (auto& objects : _objects)
	{
		for (auto& object : objects)
		{
			temp++;
			object->Render();
		}
	}

}

void Map::PostRender()
{
	for (auto& objects : _objects)
	{
		for (auto& object : objects)
		{
			object->PostRender();
		}
	}
}

void Map::ImguiRender()
{
}
