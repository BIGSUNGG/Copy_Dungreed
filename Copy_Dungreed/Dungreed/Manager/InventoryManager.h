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
	shared_ptr<Weapon> GetCurWeapon() { return _weaponSlot->operator[](*_curWeaponSlot); }

	vector<shared_ptr<Weapon>>& GetWeaponSlot() { return *_weaponSlot; }
	vector<shared_ptr<Accessory>>& GetAccessorySlot() { return *_accessory; }
	vector<shared_ptr<Item>>& GetItemSlot() { return *_itemSlot; }

	void SetCurWeaponSlot(int* slot) { _curWeaponSlot = slot; }
	void SetAccessorySlot(vector<shared_ptr<Accessory>>* slot) { _accessory = slot; }
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
	vector<shared_ptr<Accessory>>* _accessory;
	vector<shared_ptr<Item>>* _itemSlot;
};

