#include "framework.h"
#include "Map.h"

Map::Map(int level, int num)
{
	_level = level;
	_num = num;

	Reset();
}

void Map::CheckCleared()
{
	if (_cleared == true)
		return;

	_cleared = true;
	for (auto& object : _objects[Object::CREATURE])
	{
		if (object == nullptr)
			continue;

		auto creature = dynamic_pointer_cast<Creature>(object);

		if (creature->GetCreatureType() == Creature::ENEMY)
		{
			_cleared = false;
			return;
		}
	}
}

void Map::AddObject(shared_ptr<Object> addObject, int type,bool toFront)
{
	addObject->GetObjectTexture()->Update();
	shared_ptr<Quad> addQuad = addObject->GetObjectTexture();

	Vector2& pos = addObject->GetObjectTexture()->GetTransform()->GetPos();

	for (auto& objects : _objects[type])
	{
		if (addObject->GetObjectTexture()->GetTransform()->GetPos() ==
			objects->GetObjectTexture()->GetTransform()->GetPos())
		{
			return;
		}
	}

	_objectCount++;

	if (toFront)
		_objects[type].emplace(_objects[type].begin(), addObject);
	else
		_objects[type].emplace_back(addObject);

	GAME->Instancing();
}

void Map::DeleteObject(Vector2 pos, int type, bool toFront)
{
	if (toFront)
	{
		for (auto objects = _objects[type].begin(); objects != _objects[type].end(); objects++)
		{
			shared_ptr<Quad> object = objects->get()->GetObjectTexture();
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
			shared_ptr<Quad> object = _objects[type][i]->GetObjectTexture();
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

	GAME->Instancing();
}

void Map::Paste(shared_ptr<Map> copyMap)
{
	_objects.clear();
	_objects.resize(Object::_objectTypeCount);
	for (auto& object : _objects)
		object.reserve(100);

	_objects		= copyMap->GetObjects();
	_objectCount	= copyMap->GetObjectCount();

	_startPos	= copyMap->GetStartPos();
	_leftBottom = copyMap->GetLeftBottom();
	_rightTop	= copyMap->GetRightTop();

	_topDoor	= copyMap->GetTopDoor();
	_bottomDoor = copyMap->GetBottomDoor();
	_leftDoor	= copyMap->GetLeftDoor();
	_rightDoor	= copyMap->GetRightDoor();
}

void Map::Reset()
{
	_objects.clear();
	_objects.resize(Object::_objectTypeCount);
	for (auto& object : _objects)
		object.reserve(100);

	_objectCount = 0;

	_startPos	= { 5000,5000 };
	_leftBottom = { 0,0 };
	_rightTop	= { 10000,10000 };

	_topDoor	= { 0,0 };
	_bottomDoor = { 0,0 };
	_leftDoor	= { 0,0 };
	_rightDoor	= { 0,0 };
}
