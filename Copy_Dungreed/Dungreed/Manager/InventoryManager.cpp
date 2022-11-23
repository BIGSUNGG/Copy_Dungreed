#include "framework.h"
#include "InventoryManager.h"

InventoryManager* InventoryManager::_instance = nullptr;

void InventoryManager::AddGold(int gold)
{
	_gold += gold;
}

InventoryManager::InventoryManager()
{
}

InventoryManager::~InventoryManager()
{
}
