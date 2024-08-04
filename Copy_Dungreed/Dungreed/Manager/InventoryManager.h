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

	const float& GetInteractionDistance() { return _interactionDistance; }

	virtual void IncreaseGold(int value);
	virtual void DecreaseGold(int value);
	virtual void IncreaseHungry(int value);
	virtual void DecreaseHungry(int value);

	void SetCurWeaponSlot(int* slot) { _curWeaponSlot = slot; }
	void SetItemSlot(vector<shared_ptr<Item>>* slot) { _itemSlot = slot; }
	void SetWeaponSlot(vector<shared_ptr<Weapon>>* slot) { _weaponSlot = slot; }
	void SetAccessorySlot(vector<shared_ptr<Accessory>>* slot) { _accessory = slot; }

	const int& GetGold() { return _gold; }
	const int& GetCurHungry() { return _hungry; }
	const int& GetHungryMax() { return _hungryMax; }
	const int& GetPlayerLevel() { return _playerLevel; }
	const int& GetCurWeaponSlot() { return *_curWeaponSlot; }
	shared_ptr<Weapon> GetCurWeapon() { return _weaponSlot->operator[](*_curWeaponSlot); }

	vector<shared_ptr<Item>>& GetItemSlot() { return *_itemSlot; }
	vector<shared_ptr<Weapon>>& GetWeaponSlot() { return *_weaponSlot; }
	vector<shared_ptr<Accessory>>& GetAccessorySlot() { return *_accessory; }

private:
	InventoryManager();
	~InventoryManager();

	static InventoryManager* _instance;

	float _interactionDistance = 300.f;

	int _gold = 0;
	int _hungry = 100;
	int _hungryMax = 100;
	int _playerLevel = 12;

	int* _curWeaponSlot;
	vector<shared_ptr<Weapon>>* _weaponSlot = nullptr;
	vector<shared_ptr<Accessory>>* _accessory = nullptr;
	vector<shared_ptr<Item>>* _itemSlot = nullptr;
};

