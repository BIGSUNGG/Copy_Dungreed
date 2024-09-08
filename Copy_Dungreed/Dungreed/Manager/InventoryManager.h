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

	virtual void Reset();

	// 골드 증감
	virtual void IncreaseGold(int value);
	virtual void DecreaseGold(int value);

	// 허기 증감
	virtual void IncreaseHungry(int value);
	virtual void DecreaseHungry(int value);

public:
	// Getter Setter
	void SetCurWeaponSlot(int* slot) { _curWeaponSlot = slot; }
	void SetItemSlot(vector<shared_ptr<Item>>* slot) { _itemSlot = slot; }
	void SetWeaponSlot(vector<shared_ptr<Weapon>>* slot) { _weaponSlot = slot; }
	void SetAccessorySlot(vector<shared_ptr<Accessory>>* slot) { _accessory = slot; }

	const int& GetCurGold() { return _curGold; }
	const int& GetCurHungry() { return _curHungry; }
	const int& GetHungryMax() { return _maxHungry; }
	const int& GetPlayerLevel() { return _curPlayerLevel; }
	const int& GetCurWeaponSlot() { return *_curWeaponSlot; }
	const float& GetInteractionDistance() { return _interactionDistance; }
	shared_ptr<Weapon> GetCurWeapon() { return _weaponSlot->operator[](*_curWeaponSlot); }

	vector<shared_ptr<Item>>& GetItemSlot() { return *_itemSlot; }
	vector<shared_ptr<Weapon>>& GetWeaponSlot() { return *_weaponSlot; }
	vector<shared_ptr<Accessory>>& GetAccessorySlot() { return *_accessory; }

private:
	InventoryManager();
	~InventoryManager();

	static InventoryManager* _instance;

	float _interactionDistance = 300.f; // 상호작용 가능한 거리

	int _curGold = 0; // 현재 골드 값
	int _curHungry = 100; // 현재 허기 값
	int _maxHungry = 100; // 최대 허기 값
	int _curPlayerLevel = 12; // 현재 플레이어 레벨

	int* _curWeaponSlot; // 현재 들고있는 무기 슬롯
	vector<shared_ptr<Weapon>>* _weaponSlot = nullptr; // 플레이어의 무기 슬롯 
	vector<shared_ptr<Accessory>>* _accessory = nullptr; // 플레이어의 악세사리 슬롯
	vector<shared_ptr<Item>>* _itemSlot = nullptr; // 아이템 슬롯
};

