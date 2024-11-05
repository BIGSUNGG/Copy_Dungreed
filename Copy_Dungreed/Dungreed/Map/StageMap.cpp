#include "framework.h"
#include "StageMap.h"

StageMap::StageMap(int level, int num)
{
	_mapBasicInfo._level = level;
	_mapBasicInfo._num = num;

	Reset();
}

bool StageMap::CheckClear()
{
	if (_clear == true)
		return true;

	_clear = true;

	for (auto& object : _objects[Object::CREATURE])
	{
		if (object == nullptr || !object->IsActive())
			continue;

		auto creature = dynamic_pointer_cast<Creature>(object);

		if (creature->GetCreatureType() == Creature::ENEMY)
		{
			_clear = false;
			return false;
		}
	}

	OpenEvent();
}

void StageMap::AddObject(shared_ptr<Object> addObject, int type)
{
	if (addObject->GetObjectTexture() != nullptr)
	{
		addObject->GetObjectTexture()->Update();
		addObject->GetCollider()->Update();
	}
	addObject->SetOwnerMap(shared_from_this());
	_mapBasicInfo._objectCount++;
	_objects[type].emplace_back(addObject);
}

bool StageMap::DeleteObject(shared_ptr<Object> deleteObject, int type)
{
	if (deleteObject == nullptr)
		return false;

	if (_objects[type].size() <= 0)
		return false;

	for (auto iter = _objects[type].begin(); iter != _objects[type].end(); iter++)
	{
		if (*iter == deleteObject)
		{
			--_mapBasicInfo._objectCount;
			_objects[type].erase(iter);
			return true;
		}
	}

	return false;
}

bool StageMap::DeleteObject(shared_ptr<Object> deleteObject)
{
	if (deleteObject == nullptr)
		return false;

	return DeleteObject(deleteObject, deleteObject->GetType());
}

void StageMap::Paste(shared_ptr<StageMap> copyMap)
{
	_objects.clear();
	_objects.resize(Object::_objectTypeCount);
	for (auto& object : _objects)
		object.reserve(100);

	_objects		= copyMap->GetObjects();
	_mapBasicInfo._objectCount	= copyMap->GetObjectCount();

	_mapBasicInfo._startPos	= copyMap->GetStartPos();
	_mapBasicInfo._leftBottom = copyMap->GetLeftBottom();
	_mapBasicInfo._rightTop	= copyMap->GetRightTop();

	_mapBasicInfo._topDoor	= copyMap->GetTopDoor();
	_mapBasicInfo._bottomDoor = copyMap->GetBottomDoor();
	_mapBasicInfo._leftDoor	= copyMap->GetLeftDoor();
	_mapBasicInfo._rightDoor	= copyMap->GetRightDoor();
}

void StageMap::Reset()
{
	_objects.clear();
	_objects.resize(Object::_objectTypeCount);
	for (auto& object : _objects)
		object.reserve(100);

	_mapBasicInfo._objectCount = 0;

	_mapBasicInfo._startPos	= { 5000,5000 };
	_mapBasicInfo._leftBottom = { 0,0 };
	_mapBasicInfo._rightTop	= { 10000,10000 };

	_mapBasicInfo._topDoor	= { 0,0 };
	_mapBasicInfo._bottomDoor = { 0,0 };
	_mapBasicInfo._leftDoor	= { 0,0 };
	_mapBasicInfo._rightDoor	= { 0,0 };
}

void StageMap::OpenEvent()
{
	INVENTORY->DecreaseHungry(MathUtility::RandomInt(3, 10));

	for (auto& func : _openEvent)
		func();
}

void StageMap::LockEvent()
{
	for (auto& func : _lockEvent)
		func();
}
