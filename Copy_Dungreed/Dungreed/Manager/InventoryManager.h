#pragma once
class InventoryManager
{
public:
	static void Create() {
		if (_instance == nullptr)
			_instance = new InventoryManager;
	}

	static void Delete() {
		if (_instance != nullptr)
			delete _instance;
	}

	static InventoryManager* GetInstance() {
		if (_instance != nullptr)
			return _instance;
	}

	const int& GetGold() { return _gold; }
	const int& GetCurHungry() { return _hungry; }
	const int& GetHungryMax() { return _hungryMax; }
	const int& GetPlayerLevel() { return _playerLevel; }
	const int& GetCurWeaponSlot() { return *_curWeaponSlot; }
	const vector<shared_ptr<Weapon>>& GetWeaponSlot() { return *_weaponSlot; }
	shared_ptr<Weapon> GetCurWeapon() { return _weaponSlot->operator[](*_curWeaponSlot); }

	void SetCurWeaponSlot(int* slot) { _curWeaponSlot = slot; }
	void SetWeaponSlot(vector<shared_ptr<Weapon>>* slot) { _weaponSlot = slot; }
	void SetItemSlot(vector<shared_ptr<Item>>* slot) { _itemSlot = slot; }

private:
	InventoryManager();
	~InventoryManager();

	static InventoryManager* _instance;

	int _gold = 0;
	int _hungry = 0;
	int _hungryMax = 100;
	int _playerLevel = 1;

	int* _curWeaponSlot;
	vector<shared_ptr<Weapon>>* _weaponSlot;
	vector<shared_ptr<Item>>* _itemSlot;
};

