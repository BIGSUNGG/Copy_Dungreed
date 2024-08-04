#include "framework.h"
#include "InventoryManager.h"

InventoryManager* InventoryManager::_instance = nullptr;

void InventoryManager::IncreaseGold(int value)
{
	_gold += value;
}

void InventoryManager::DecreaseGold(int value)
{
	_gold -= value;
	if (_gold < 0)
		_gold = 0;
}

void InventoryManager::IncreaseHungry(int value)
{
	_hungry += value;

}

void InventoryManager::DecreaseHungry(int value)
{
	_hungry -= value;
	if (_hungry < 0)
		_hungry = 0;
}

InventoryManager::InventoryManager()
{
}

InventoryManager::~InventoryManager()
{
}
