#include "framework.h"
#include "Map.h"

Map::Map(int level, int num, char direction)
{
	_level = level;
	_num = num;

	Reset();
}

void Map::AddObject(shared_ptr<Object> addObject, int type,bool toFront)
{
	addObject->GetTexture()->Update();
	shared_ptr<Quad> addQuad = addObject->GetTexture();

	Vector2& pos = addObject->GetTexture()->GetTransform()->GetPos();

	for (auto& objects : _objects[type])
	{
		if (addObject->GetTexture()->GetTransform()->GetPos() ==
			objects->GetTexture()->GetTransform()->GetPos())
		{
			return;
		}
	}

	_objectCount++;
	
	if (toFront)
		_objects[type].emplace(_objects[type].begin(), addObject);
	else
		_objects[type].emplace_back(addObject);
}

void Map::DeleteObject(Vector2 pos, int type, bool toFront)
{
	if (toFront)
	{
		for (auto objects = _objects[type].begin(); objects != _objects[type].end(); objects++)
		{
			shared_ptr<Quad> object = objects->get()->GetTexture();
			if (pos.x > object->Left() && pos.x < object->Right() &&
				pos.y < object->Top() && pos.y > object->Bottom())
			{
				_objects[type].erase(objects);
				_objectCount--;
				break;
			}
		}
	}
	else
	{
		for (int i = _objects[type].size() - 1; i > 0; i--)
		{
			shared_ptr<Quad> object = _objects[type][i]->GetTexture();
			if (pos.x > object->Left() && pos.x < object->Right() &&
				pos.y < object->Top() && pos.y > object->Bottom())
			{
				auto iter = _objects[type].begin() + i;
				_objects[type].erase(iter);
				_objectCount--;
				break;
			}
		}
	}
}

void Map::Reset()
{
	_objects.clear();
	_objects.resize(6);
	for (auto& object : _objects)
		object.reserve(100);
	_objectCount = 0;
}
