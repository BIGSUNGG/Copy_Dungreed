#include "framework.h"
#include "InventoryManager.h"

InventoryManager* InventoryManager::_instance = nullptr;

void InventoryManager::Reset()
{
	_curGold = 0;
	_curHungry = 100;
}

void InventoryManager::IncreaseGold(int value)
{
	_curGold += value;
}

void InventoryManager::DecreaseGold(int value)
{
	_curGold -= value;
	if (_curGold < 0)
		_curGold = 0;
}

void InventoryManager::IncreaseHungry(int value)
{
	_curHungry += value;

}

void InventoryManager::DecreaseHungry(int value)
{
	_curHungry -= value;
	if (_curHungry < 0)
		_curHungry = 0;
}

InventoryManager::InventoryManager()
{
}

InventoryManager::~InventoryManager()
{
}
