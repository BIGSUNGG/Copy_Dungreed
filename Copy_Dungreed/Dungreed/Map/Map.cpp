#include "framework.h"
#include "Map.h"

Map::Map(int level, int num)
{
	_level = level;
	_num = num;

	Reset();
}

bool Map::CheckCleared()
{
	if (_cleared == true)
		return true;

	_cleared = true;

	for (auto& object : _objects[Object::CREATURE])
	{
		if (object == nullptr || !object->IsActive())
			continue;

		auto creature = dynamic_pointer_cast<Creature>(object);

		if (creature->GetCreatureType() == Creature::ENEMY)
		{
			_cleared = false;
			return false;
		}
	}

	OpenEvent();
}

void Map::AddObject(shared_ptr<Object> addObject, int type)
{
	if (addObject->GetObjectTexture() != nullptr)
	{
		addObject->GetObjectTexture()->Update();
		addObject->GetCollider()->Update();
	}
	addObject->SetOwnerMap(shared_from_this());
	_objectCount++;
	_objects[type].emplace_back(addObject);
}

bool Map::DeleteObject(shared_ptr<Object> deleteObject, int type)
{
	for (auto iter = _objects[type].begin(); iter != _objects[type].end(); iter++)
	{
		if (*iter == deleteObject)
		{
			--_objectCount;
			_objects[type].erase(iter);
			return true;
		}
	}

	return false;
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

void Map::OpenEvent()
{
	for (auto& func : _openEvent)
		func();
}

void Map::LockEvent()
{
	for (auto& func : _lockEvent)
		func();
}
