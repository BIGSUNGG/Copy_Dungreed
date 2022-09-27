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

	const int& GetPlayerLevel() { return _playerLevel; }
	const int& GetCurWeaponSlot() { return *_curWeaponSlot; }
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
	int _playerLevel = 1;

	int* _curWeaponSlot;
	vector<shared_ptr<Weapon>>* _weaponSlot;
	vector<shared_ptr<Item>>* _itemSlot;
};

